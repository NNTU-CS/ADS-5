cmake_minimum_required(VERSION 3.10)
project(ADS-5-test)

include(GoogleTest)

set(TEST_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/tests.cpp
)

add_executable(ADS-5.test ${TEST_SOURCES})

target_link_libraries(ADS-5.test PRIVATE 
    ADS-5 
    GTest::GTest 
    GTest::Main
)

gtest_discover_tests(ADS-5.test)
