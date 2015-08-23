#pragma once
#include <chrono>
#include <future>


void some_task()
{
    std::cout << "working...\n";
}

void too_long_task()
{
    std::cout << "I will work too long :(\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
    std::cout << "end of work...";
}


void chrono()
{
    using namespace std::chrono;
    std::cout << "ratio num:" << std::ratio<1,25>::num << "\n";
    std::cout << "ratio num:" << std::ratio<1,25>::den << "\n";
    duration<double, std::ratio<1,1000>> d;

    std::chrono::milliseconds ms(5000);
    std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds>(ms);
    std::cout << "5000 ms to s: " << s.count() << "\n";

    std::chrono::seconds g = std::chrono::seconds(5)+ std::chrono::minutes(5);
    std::cout << "5s + 5m = " << g.count() << "seconds\n";


    std::packaged_task<void()> t(some_task);

    std::future<void> f = t.get_future();
    t();
    if(f.wait_for(milliseconds(35)) == std::future_status::ready)
        f.get();


    auto start = std::chrono::high_resolution_clock::now();

    std::packaged_task<void()> t2(too_long_task);

    std::future<void> f2 = std::async(std::launch::async, too_long_task);
    if(f2.wait_for(milliseconds(29)) == std::future_status::timeout)
    {
        std::cout << "timeout\n";
    }
    else
    {
        std::cout << "we dont have a timeout!\n";
    }
    std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> stop = std::chrono::high_resolution_clock::now();
    std::chrono::nanoseconds difference = stop-start;
    std::chrono::microseconds elapsed = std::chrono::duration_cast<std::chrono::microseconds>(difference);
    std::cout << "elapsed time in microseconds: " << elapsed.count() << "\n";

}
