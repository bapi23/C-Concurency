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

    return 0;
}

