#pragma once
#include <future>




void do_work()
{
    std::cout << "work...\n";
}

void packaged_task()
{
    std::packaged_task<void()> task(do_work);
    auto fut = task.get_future();
    task();
    //fut.get();

}
