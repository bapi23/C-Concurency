#include <iostream>
#include <thread>
#include <unistd.h>
#include "hello_world.h"
#include "raii.h"
#include "thread.h"
#include "ThreadSafeStack.h"
#include "lock.h"
#include "hierarchical_mutex.h"
#include "unique_lock.h"
#include "call_once.h"
#include "shared_mutex.h"
#include "threadsafe_queue.h"
#include "packaged_task.h"
#include "promise.h"
#include "chrono.h"
#include "async_exception.h"

int main()
{
    std::cout << "--------------- hello world -----------------\n";
    hello_world();
    std::cout << "--------------- raii -----------------\n";
    raii();
    std::cout << "--------------- thread -----------------\n";
    thread();
    std::cout << "--------------- thread safe stack -----------------\n";
    threadsafestack_test();
    std::cout << "--------------- lock -----------------\n";
    lock();
    std::cout << "--------------- hierarchical mutex -----------------\n";
    hierarchical_mutex_test();
    std::cout << "--------------- unique_lock -----------------\n";
    unique_lock_test();
    std::cout << "--------------- call_once -----------------\n";
    call_once_test();
    std::cout << "--------------- shared_mutex -----------------\n";
    shared_mutex_test();
    std::cout << "--------------- packaged_task -----------------\n";
    packaged_task();
    std::cout << "--------------- promise -----------------\n";
    promise();
    std::cout << "--------------- shared_future -----------------\n";
    shared_future();
    std::cout << "--------------- chrono -----------------\n";
    chrono();
    std::cout << "--------------- async_exception -----------------\n";
    async_exception();

    return 0;
}

