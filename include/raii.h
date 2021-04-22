#pragma once
#include <thread>


template<typename Callable, typename ...Args>
class guarded_thread
{
public:
    guarded_thread(Callable&& t, Args&&... args):
        t(std::forward<Callable>(t), std::forward<Args>(args)...)
    {
        std::cout << "thread_guard - creating guarded thread\n";
    }

    ~guarded_thread()
    {
        if(t.joinable())
        {
            std::cout << "thread_guard joining thread\n";
            t.join();
        }
    }

    guarded_thread(guarded_thread&& other)
    {
        this->t = std::move(other.t);
    }

    guarded_thread& operator=(guarded_thread&& other)
    {
        this->t = std::move(other.t);
        return *this;
    }

    guarded_thread(const guarded_thread&) = delete;
    guarded_thread& operator=(const guarded_thread&) = delete;

private:
    std::thread t;
};

template<typename Callable, typename ...Args>
guarded_thread<Callable, Args...> create_guarded_thread(Callable&& t, Args&&... args)
{
    return guarded_thread<Callable, Args...>(std::forward<Callable>(t), std::forward<Args>(args)...);
}


void raii()
{
    auto guarded_thread1 = create_guarded_thread([](){ std::cout << "working...\n";});
}
