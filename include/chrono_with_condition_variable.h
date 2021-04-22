#pragma once

#include <condition_variable>
#include <mutex>
#include <chrono>
#include <thread>


std::mutex m;
std::condition_variable cv;
bool done = false;

void work()
{
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(400ms);
    done = true;
    cv.notify_one();
}


void chrono_with_condition_variable()
{

    std::thread t(work);

    auto const timeout = std::chrono::steady_clock::now()+std::chrono::milliseconds(300);
    std::unique_lock<std::mutex> lock(m);

    std::cout << "working...\n";
    if(cv.wait_until(lock, timeout, [](){ return done; }))
    {
        std::cout << " no timeout!\n";
    }
    else
    {
        std::cout << "timeout ;/\n";
    }

    t.join();
    std::cout << "done\n";

}
