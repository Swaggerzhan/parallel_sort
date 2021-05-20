cmake_minimum_required(VERSION 2.8)
project(Thread)

set(CMAKE_CXX_FLAGS
        -lpthread
        )

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE DEBUG)

add_executable(Thread

        main.cpp
        Condition.h Condition.cpp
        Mutex.h Thread.h Thread.cpp
        ThreadPool.h ThreadPool.cpp
        ParallelSort.h
        ParallelSort.cpp)