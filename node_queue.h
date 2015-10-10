#ifndef NODE_QUEUE
#define NODE_QUEUE
#include <memory>
#include <mutex>
#include <thread>
#include <condition_variable>


template <class T>
class node_queue
{
private:
    struct node
    {
        std::shared_ptr<T> m_data;
        std::unique_ptr<node> next;
    };

    node* get_tail()
    {
        std::lock_guard<std::mutex> l(tail_mutex);
        return m_tail;
    }

    std::unique_ptr<node> pop()
    {
        std::lock_guard<std::mutex> l(m_head_mutex);
        if(m_head.get() == get_tail())
            return nullptr;

        std::unique_ptr<node> old_head = std::move(m_head);
        m_head = std::move(old_head->next);
        return old_head;
    }

    std::shared_ptr<node> wait_pop_head()
    {
        std::unique_lock<std::mutex> l(m_head_mutex);
        cv.wait(l, [&]{ return m_head.get() != get_tail();});
        std::unique_ptr<node> old_head = std::move(m_head);
        m_head = std::move(old_head->next);
        return old_head;
    }

    void wait_pop_head(T& value)
    {
        std::unique_lock<std::mutex> l(m_head_mutex);
        cv.wait(l, [&]{ return m_head.get() != get_tail();});
        std::unique_ptr<node> old_head = std::move(m_head);
        m_head = std::move(old_head->next);
        value = *old_head->m_data;
    }

    std::mutex tail_mutex;
    std::mutex m_head_mutex;
    std::unique_ptr<node> m_head;
    node *m_tail;
    std::condition_variable cv;

public:
    node_queue():
        m_head(new node),
        m_tail(m_head.get())
    {

    }
    node_queue& operator=(const node_queue&) = delete;
    node_queue(const node_queue&) = delete;

    std::shared_ptr<T> try_pop()
    {
        std::unique_ptr<node> head = pop();
        if(head)
            return head->m_data;
        else
            return std::shared_ptr<T>();
    }

    void push(T new_value)
    {
        std::shared_ptr<T> new_data(std::make_shared<T>(std::move(new_value)));
        std::unique_ptr<node> empty_node(std::make_unique<node>());
        node* const new_tail = empty_node.get();

        std::lock_guard<std::mutex> l(tail_mutex);
        m_tail->m_data = new_data;
        m_tail->next = std::move(empty_node);
        m_tail = new_tail;
        cv.notify_one();
        
    }

    std::shared_ptr<T> wait_and_pop()
    {
        return wait_pop_head()->m_data;
    }

    void wait_and_pop(T& value)
    {
        return wait_pop_head(value);
    }

    bool empty()
    {
        std::lock_guard<std::mutex> l(m_head_mutex);
        return m_head.get() == get_tail();
    }
};

node_queue<int> queue_to_test;

void test_push(int iterations_number)
{
    for(int i = 0; i < iterations_number; ++i)
    {
        queue_to_test.push(42);
    }
}

void test_pop(int iterations_number)
{
    for(int i = 0; i < iterations_number; ++i)
    {
        queue_to_test.try_pop();
    }
}

void test_wait_pop(int iterations_number)
{
    for(int i = 0; i < iterations_number; ++i)
    {
        queue_to_test.wait_and_pop();
    }
}

void test_wait_pop2(int iterations_number)
{
    for(int i = 0; i < iterations_number; ++i)
    {
        int val;
        queue_to_test.wait_and_pop(val);
    }
}


void test_node_queue()
{
    std::thread push_thread(test_push, 30000);
    std::thread pop_thread(test_pop, 10000);
    std::thread wait_pop_thread(test_wait_pop, 10000);
    std::thread wait_pop_thread2(test_wait_pop2, 10000);

    push_thread.join();
    pop_thread.join();
    wait_pop_thread.join();
    wait_pop_thread2.join();

    std::cout << queue_to_test.empty();
}

#endif // NODE_QUEUE

