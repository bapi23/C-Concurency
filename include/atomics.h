#pragma once
#include <atomic>
#include <thread>

std::atomic<int> XX(0), YY(0);
int r1, r2;


void thread1()
{
    YY.store(1);
    YY.store(2);
    YY.store(3);
    YY.store(4);
    YY.store(5);
    YY.store(6);
    YY.store(7);
    YY.store(8);
    YY.store(9);
    YY.store(10);
}

void thread2()
{
    YY.store(1);
    YY.store(2);
    YY.store(3);
    YY.store(4);
    YY.store(5);
    YY.store(6);
    YY.store(7);
    YY.store(8);
    YY.store(9);
    YY.load();
    YY.store(11);
}


std::atomic<bool> boolAtomic1;


template <class T>
struct Node
{
    T data;
    Node* nextNode;
    Node(const T& data): data(data), nextNode(nullptr){}
};


template <class T>
class stack
{
    std::atomic<Node<T>*> head;
public:
    void push(const T& data)
    {
        Node<T>* newNode = new Node<T>(data);

        //seems like this line can be ommited cause compare_exchange_strong will execute this operation if nextNode will be nullPtr
        newNode->nextNode = head.load();

        head.compare_exchange_strong(newNode->nextNode, newNode);
    }

};


class NonAtomicType
{
private:
    int data;
public:
    NonAtomicType& operator = (const NonAtomicType& t)
    {
        this->data = t.data;
        return *this;
    }
};

//std::atomic<NonAtomicType> nonAtomic;





void atomics()
{
    std::thread t1(thread1);
    std::thread t2(thread2);

    t1.join();
    t2.join();

    std::cout << "r1: " << YY.load() << " r2: " << r2 << "\n";


    boolAtomic1 = true;
    std::cout << "bool atomic:" << boolAtomic1.load() << "\n";
    boolAtomic1.store(true);
    std::cout << "bool atomic:" << boolAtomic1.load() << "\n";
    bool expected = true;
    bool result = boolAtomic1.compare_exchange_weak(expected, false);

    std::cout << "expected: "  << expected << "\n";
    std::cout << "result: " <<result << "\n";
    std::cout << "atomic value: " << boolAtomic1.load() << "\n";
    std::cout << "bool is lock free: " << boolAtomic1.is_lock_free() << "\n";
}
