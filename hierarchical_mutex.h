#pragma once

#include <mutex>
#include <limits>
#include <cassert>

class hierarchical_mutex
{
public:
    hierarchical_mutex(unsigned int hierarchyLevel):
        m_hierarchyLevel(hierarchyLevel)
    {}

    void lock()
    {
        assert(s_currentHierarchyLevel > m_hierarchyLevel);
        m_mutex.lock();
        m_previousLevel = s_currentHierarchyLevel;
        s_currentHierarchyLevel = m_hierarchyLevel;
    }

    void unlock()
    {
        m_mutex.unlock();
        s_currentHierarchyLevel = m_previousLevel;
    }

    void tryLock() noexcept
    {
        assert(s_currentHierarchyLevel > m_hierarchyLevel);
        if(m_mutex.try_lock())
        {
            m_previousLevel = s_currentHierarchyLevel;
            s_currentHierarchyLevel = m_hierarchyLevel;
        }
    }

    hierarchical_mutex(const hierarchical_mutex&) = delete;
    hierarchical_mutex& operator=(const hierarchical_mutex&) = delete;

private:
    static thread_local unsigned int s_currentHierarchyLevel;
    unsigned int m_hierarchyLevel;
    unsigned int m_previousLevel = 0;
    std::mutex m_mutex;
};

thread_local unsigned int hierarchical_mutex::s_currentHierarchyLevel = std::numeric_limits<unsigned int>::max();


hierarchical_mutex layer2Mutex(1);
hierarchical_mutex layer1Mutex(2);

void layer2()
{
    std::lock_guard<hierarchical_mutex> lock(layer2Mutex);
    std::cout << "Second layer code\n";
}

void layer1()
{
    std::lock_guard<hierarchical_mutex> lock(layer1Mutex);
    std::cout << "First layer code\n";
    layer2();
}


void layer1_bad()
{
    std::lock_guard<hierarchical_mutex> lock(layer1Mutex);
    std::cout << "First layer bad code\n";
}

void layer2_bad()
{
    std::lock_guard<hierarchical_mutex> lock(layer2Mutex);
    std::cout << "Second layer bad code\n";
    layer1_bad();
}


void hierarchical_mutex_test()
{
    layer1();
    //layer2_bad(); assertion failed!
}
