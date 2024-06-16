#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include <coro/coro.hpp>
#include <coro/generator.hpp>
#include <condition_variable>
#include <cstddef>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace stochastic
{
    class Thread_pool
    {
    private:
        std::vector<std::jthread> threads;
        std::queue<std::function<void()>> tasks;
        std::mutex tasks_mutex;
        std::condition_variable cv;
        std::atomic<bool> terminate{false};

        std::function<void()> pop()
        {
            auto task = std::function<void()>{};
            auto lock = std::unique_lock(tasks_mutex);
            while (tasks.empty() && !terminate)
                cv.wait(lock);  // release,wait,acquire
            if (!terminate && !tasks.empty()) {
                task = std::move(tasks.front());
                tasks.pop();
            }
            return task;
        }

        void push(std::function<void()> task)
        {
            auto lock = std::unique_lock(tasks_mutex);
            tasks.push(std::move(task));
            cv.notify_all();
        }

        void stop()
        {
            auto lock = std::unique_lock(tasks_mutex);
            terminate = true;
            cv.notify_all();
        }

    public:
        explicit Thread_pool(size_t num)
        {
            for (size_t i = 0; i < num; ++i) {
                this->threads.emplace_back([this] {
                    while (!terminate) {
                        auto task = pop();
                        if (task)
                            task();
                    }
                });
            }
        }

        template <typename Fn, typename Ret = std::result_of_t<std::decay_t<Fn>()>>
        std::future<Ret> async(Fn&& fn)
        {
            // promise is not copyable, thus wrap into a smart pointer:
            auto ret = std::make_shared<std::promise<Ret>>();
            push([ret, fn = std::forward<Fn>(fn)]() mutable {
                try {
                    ret->set_value(fn());
                } catch (...) {
                    ret->set_exception(std::current_exception());
                }
            });
            return ret->get_future();
        }

        template <typename Fn, typename Out = std::invoke_result_t<Fn>>
        std::vector<std::future<Out>> dispatch(Fn&& fn, const size_t& amount)
        {
            auto res = std::vector<std::future<Out>>( amount );
            for (auto& r : res) {
                r = async(fn);
            }
            return res;
        }

        ~Thread_pool()
        {
            stop();
            for (auto& thread : threads) {
                thread.join();
            }
        }
    };
}  // namespace stochastic

#endif