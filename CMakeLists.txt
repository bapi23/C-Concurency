cmake_minimum_required(VERSION 3.10)
project(CppConcurency)

find_package(Boost COMPONENTS system thread REQUIRED)
find_package(Threads REQUIRED)

add_executable(concurrency src/main.cpp)
target_link_libraries(concurrency PRIVATE ${Boost_LIBRARIES} Threads::Threads)
target_include_directories(concurrency PRIVATE include ${Boost_INCLUDE_DIRS})