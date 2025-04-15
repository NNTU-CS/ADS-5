cmake_minimum_required(VERSION 3.10)
project(ADS-5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -O3 -g -pthread")

add_library(ADS-5 STATIC
    src/alg.cpp
    src/tstack.h
)

cmake_policy(SET CMP0079 NEW)

find_package(Threads REQUIRED)
target_link_libraries(ADS-5 PRIVATE Threads::Threads)

add_subdirectory(test)
