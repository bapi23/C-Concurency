#pragma once
#include <stdexcept>
#include <future>


void function_that_throw()
{
    throw std::logic_error("what od exception");
}



void async_exception()
{
    auto f = std::async(std::launch::async, function_that_throw);
    try
    {
        f.get();
    }
    catch(const std::exception& e)
    {
        std::cout << "exception catched : " <<  e.what() << "\n";
    }

}
