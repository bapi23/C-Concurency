#pragma once
#include <thread>

void byRef(int& a)
{
    a = 99;
}

void byRRef(std::unique_ptr<int> a)
{
    *a = 3;
}

void thread()
{
    std::cout << "Num of hardware threads: " << std::thread::hardware_concurrency() << "\n";
    int localA = 78;
    std::thread t1(byRef, std::ref(localA));
    t1.join();
    std::cout << "local A: " << localA << "\n";

    std::unique_ptr<int> localB(new int(78));
    std::cout << "local B1: " << *localB << "\n";
    std::thread t2(byRRef, std::move(localB));
    t2.join();
    std::cout << "local B2: " << bool(localB) << "\n";
}
