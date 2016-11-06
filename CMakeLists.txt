cmake_minimum_required(VERSION 3.0)
project(mutest)

add_library(mutest_nomain STATIC
    mutest/event_sink.cpp
    mutest/detail/registry.cpp
    mutest/detail/repr.cpp
    )
target_include_directories(
    mutest_nomain
    INTERFACE .
    )

add_library(mutest STATIC
    utest_main.cpp
    )
target_link_libraries(mutest mutest_nomain)

add_executable(mutest_test
    test/utest_test.cpp
    )
target_link_libraries(mutest_test mutest)
