#pragma once
#include <mutex>
#include <memory>
#include <thread>

std::unique_ptr<int> p;
std::once_flag flag;

void function()
{
    std::call_once(flag, [](){ p.reset(new int(9));
                                 std::cout << "initialised!\n";});
}

void call_once_test()
{
    std::thread t1(function);
    std::thread t2(function);

    t1.join();
    t2.join();
    std::cout << "initialised value:" << *p << "\n";
}
