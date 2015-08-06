#pragma once
#include <stack>
#include <memory>
#include <mutex>
#include <thread>
#include <exception>
#include <iostream>


struct EmptyStack: public std::exception
{

};

template<typename T>
class thread_safe_stack
{
public:
    void push(const T& t)
    {
        std::lock_guard<std::mutex> l(m);
        //std::cout << "pushing elem index: " << data.size() << "\n";
        data.push(t);
    }

    auto pop()
    {
        std::lock_guard<std::mutex> l(m);
        if(data.empty())
            return std::shared_ptr<T>();
        //std::cout << "popping elem index: " << data.size() << "\n";
        auto top = std::make_shared<T>(data.top());
        data.pop();
        return top;
    }

    thread_safe_stack() = default;
    thread_safe_stack(const thread_safe_stack& stack)
    {
        std::lock_guard<std::mutex> l(m);
        this->data = stack.data;
    }

    auto size()
    {
        std::lock_guard<std::mutex> l(m);
        return data.size();
    }

    thread_safe_stack operator = (const thread_safe_stack& stack) = delete;

private:
    std::stack<T> data;
    std::mutex m;
};

thread_safe_stack<int> g_stack;

void pop_test()
{
    for(int i = 0; i < 1000; ++i)
    {
        while(!g_stack.pop());
    }
}

void push_test()
{
    for(int i = 0; i < 1000; ++i)
    {
        g_stack.push(i);
    }
}

void threadsafestack_test()
{
    std::thread pushThread(push_test);
    std::thread popThread(pop_test);

    pushThread.join();
    popThread.join();
    std::cout << "should be 0 size: " << g_stack.size() <<"\n";
}
