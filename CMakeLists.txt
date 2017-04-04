cmake_minimum_required(VERSION 3.0)
project(mutest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(mutest_nomain STATIC
    include/mutest/exec.h
    include/mutest/test.h
    include/mutest/utest.h

    src/copy_error_tester.h
    src/detail/binary_op.h
    src/detail/char_stream.h
    src/detail/check.h
    src/detail/expr.h
    src/detail/list.h
    src/detail/registry.cpp
    src/detail/registry.h
    src/detail/repr.cpp
    src/detail/repr.h
    src/event_sink.cpp
    src/event_sink.h
    )

target_include_directories(mutest_nomain PUBLIC include)

add_library(mutest STATIC
    src/utest_main.cpp
    )

target_link_libraries(mutest mutest_nomain)

add_executable(mutest_test
    test/utest_test.cpp
    )
target_link_libraries(mutest_test mutest)

enable_testing()
add_test(NAME mutest_test COMMAND mutest_test)
