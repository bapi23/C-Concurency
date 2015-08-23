#pragma once

#include <condition_variable>
#include <mutex>
#include <chrono>


std::mutex m;
std::condition_variable cv;
bool done;


void chrono_with_condition_variable()
{

    auto const timeout = std::chrono::steady_clock::now();+std::chrono::milliseconds(30);
    std::unique_lock<std::mutex> lock(m);
    while(!done)
    {
        if(cv.wait_until(lock, timeout) == std::cv_status::timeout)
            break;
    }

}
