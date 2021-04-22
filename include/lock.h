#pragma once
#include <mutex>
#include <thread>
#include <cassert>

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
        std::lock(lhs.m, rhs.m);
        std::lock_guard<std::mutex> l(lhs.m, std::adopt_lock);
        std::lock_guard<std::mutex> r(rhs.m, std::adopt_lock);
        std::swap(lhs.detail_, rhs.detail_);
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

void lock()
{
    std::thread t12(function_swap12);
    std::thread t21(function_swap21);

    t12.join();
    t21.join();
    std::cout << "detail 1 :" << x1.detail() << " x2 detail: " << x2.detail() << "\n";
    assert(x1.detail() != x2.detail());
}
