cmake_minimum_required(VERSION 3.14)
project(ADS-5-test)

include(GoogleTest)
find_package(GTest REQUIRED)

add_executable(ADS-5.test tests.cpp)
target_link_libraries(ADS-5.test PRIVATE 
    ADS-5 
    GTest::GTest 
    GTest::Main
)

gtest_discover_tests(ADS-5.test)
