cmake_minimum_required(VERSION 3.21)
project(portable_test_lib)

set(CMAKE_CXX_STANDARD 17)

add_executable(portable_test_lib example.cpp testlib.h)
