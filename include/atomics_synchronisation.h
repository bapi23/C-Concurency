#pragma once
#include <atomic>
#include <thread>
#include <cassert>


std::atomic<int> x;
std::atomic<int> y;
std::atomic<int> g;
std::atomic<int> counter;

void t1()
{
    x.store(2);
}

void t2()
{
    y.store(2);
}

void t3()
{
    x.load();
    assert(x==1);
}

void t4()
{
    y.load();
    assert(y==1);
}

void z1()
{
    x.store(1, std::memory_order_relaxed);
}

void z2()
{
    y.store(1, std::memory_order_relaxed);
}

void z3()
{
    if(y.load(std::memory_order_relaxed) == 1 && x.load(std::memory_order_relaxed) == 0)
        counter++;
}

void z4()
{
    if(y.load(std::memory_order_relaxed) == 0 && x.load(std::memory_order_relaxed) == 1)
        counter++;
}




void atomics_synchronisation()
{

//    for(int i = 0; i < 10000; ++i)
//    {
//        x = 1;
//        y = 1;

//        std::thread th4(t1);
//        std::thread th3(t2);
//        std::thread th2(t3);
//        std::thread th1(t4);


//        th4.join();
//        th3.join();
//        th2.join();
//        th1.join();
//    }

//    for(int i = 0; i < 10000; ++i)
//    {
//        counter = 0;
//        x = 0;
//        y = 0;
//        g = 0;

//        std::thread th1(z1);
//        std::thread th2(z2);
//        std::thread th3(z3);
//        std::thread th4(z4);


//        th1.join();
//        th2.join();
//        th3.join();
//        th4.join();
//        assert(counter <= 1);
//    }
}
