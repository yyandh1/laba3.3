cmake_minimum_required(VERSION 3.10)

project(HashTableBenchmark)

set(CMAKE_CXX_STANDARD 17)

find_package(benchmark REQUIRED)

add_executable(main_test main_test.cpp hashtable.cpp List1.cpp List2.cpp massive.cpp queue.cpp stack.cpp tree.cpp)
target_link_libraries(main_test benchmark::benchmark)