cmake_minimum_required(VERSION 3.24)
project(concurrency)

set(CMAKE_CXX_STANDARD 17)

add_executable(concurrency  concurrent_queue.h thread_pool.h thead_pool_run.cpp)
