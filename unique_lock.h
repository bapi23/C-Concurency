#pragma once
#include <unique_lock.h>

namespace
{
class X
{
public:
    X(int detail):
        detail_(detail)
    {}

    friend void swap(X& lhs, X& rhs)
    {
        if(&lhs == &rhs)
            return;
        std::unique_lock<std::mutex> l(lhs.m, std::defer_lock);
        std::unique_lock<std::mutex> r(rhs.m, std::defer_lock);
        std::lock(l, r);
        std::swap(lhs.detail_, rhs.detail_);
        //std::cout << "owns_lock l: " << l.owns_lock();
        //std::cout << "owns_lock r: " << r.owns_lock();
    }

    auto detail()
    {
        return detail_;
    }

private:
    int detail_;
    std::mutex m;
};

X x1(7);
X x2(9);

void function_swap12()
{
    for(int i = 0; i < 10000; ++i)
    {
        swap(x1, x2);
    }
}

void function_swap21()
{
    for(int i = 0; i < 10000; ++i)
    {
        swap(x2,x1);
    }
}


std::unique_lock<std::mutex> getLock()
{
    std::mutex localMutex;
    std::cout << &localMutex << "\n";
    std::unique_lock<std::mutex> ul(localMutex);
    return ul;
}

void process()
{
    std::unique_lock<std::mutex> ul(getLock());
    std::cout << "process data\n";
    auto* mutex = ul.mutex();
    std::cout << mutex << "\n";
    mutex->native_handle();
}

void unique_lock_test()
{
    std::thread t12(function_swap12);
    std::thread t21(function_swap21);

    t12.join();
    t21.join();
    std::cout << "detail 1 :" << x1.detail() << " x2 detail: " << x2.detail() << "\n";
    assert(x1.detail() != x2.detail());

    std::thread t3(process);
    t3.join();
}
}
