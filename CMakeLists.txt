cmake_minimum_required(VERSION 3.14)
project(ADS-5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -pthread")

add_library(ADS-5 STATIC
    src/alg.cpp
    src/tstack.h
)

add_subdirectory(test)
