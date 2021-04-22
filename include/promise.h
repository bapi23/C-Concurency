#pragma once
#include <future>

std::promise<int> prom;

void func()
{
    prom.set_value(54);
}

void promise()
{
    auto f = prom.get_future();
    std::thread t(func);
    t.join();
    std::cout << "promise result:" << f.get();
}


namespace
{
std::promise<int> prom;

void func()
{
    prom.set_value(54);
}

void shared_future()
{
    auto f = prom.get_future();
    std::thread t(func);
    t.join();
    std::cout << "promise result:" << f.get();
}
}
