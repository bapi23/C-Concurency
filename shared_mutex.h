#pragma once
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/shared_lock_guard.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>
#include <thread>
#include <QElapsedTimer>
#include <stdlib.h>

template<typename Data,
         typename MutexType,
         typename ReaderLocker,
         typename WriterLocker>
class DataProvider
{
public:
    DataProvider()
    {
        entries.push_back(Data{});
    }

    void addItem(Data&& item)
    {
        WriterLocker guard(mutex);
        entries.push_back(std::forward<Data>(item));
    }

    Data getEntry(int index)
    {
        ReaderLocker guard(mutex);
        return entries.at(index);
    }


private:
    std::vector<Data> entries;
    MutexType mutex;
};


DataProvider<int,
            boost::shared_mutex,
            boost::shared_lock_guard<boost::shared_mutex>,
            boost::lock_guard<boost::shared_mutex>> dataProviderSharedMutex;

DataProvider<int,
            boost::mutex,
            boost::lock_guard<boost::mutex>,
            boost::lock_guard<boost::mutex>> dataProviderMutex;


void writerFunc()
{
    for(int i = 0; i < 1000; ++i)
    {
        using namespace std::literals;
        dataProviderSharedMutex.addItem(666);
        std::this_thread::sleep_for(10ms);
    }
}

void readerFunc()
{
    for(int i = 0; i < 10000; ++i)
    {
        using namespace std::literals;
        dataProviderSharedMutex.getEntry(0);
        std::this_thread::sleep_for(0ms);
    }
}

void writerFunc2()
{
    for(int i = 0; i < 1000; ++i)
    {
        using namespace std::literals;
        dataProviderMutex.addItem(666);
        std::this_thread::sleep_for(10ms);
    }
}

void readerFunc2()
{
    for(int i = 0; i < 10000; ++i)
    {
        using namespace std::literals;
        dataProviderMutex.getEntry(0);
        std::this_thread::sleep_for(0ms);
    }
}



void shared_mutex_test()
{
//    {
//        using namespace std::literals;
//        QElapsedTimer timer;
//        timer.start();
//        boost::thread writer(writerFunc);
//        boost::thread reader1(readerFunc);
//        boost::thread reader2(readerFunc);
//        boost::thread reader3(readerFunc);

//        writer.join();
//        reader1.join();
//        reader2.join();
//        reader3.join();
//        int elapsed = timer.elapsed();

//        std::cout << "Elapsed time = " << elapsed;
//    }
//    {
//        using namespace std::literals;
//        QElapsedTimer timer;
//        timer.start();
//        boost::thread writer(writerFunc2);
//        boost::thread reader1(readerFunc2);
//        boost::thread reader2(readerFunc2);
//        boost::thread reader3(readerFunc2);

//        writer.join();
//        reader1.join();
//        reader2.join();
//        reader3.join();
//        int elapsed = timer.elapsed();

//        std::cout << "Elapsed time = " << elapsed;
//    }
}
