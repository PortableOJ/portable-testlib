cmake_minimum_required(VERSION 3.21)
project(portable_test_lib)

set(CMAKE_CXX_STANDARD 11)

add_executable(portable_test_lib example.cpp testlib.h)

include_directories(.)

add_executable(ALL_SAME standard/ALL_SAME.cpp testlib.h)
add_executable(IGNORE_END_OF_FILE standard/IGNORE_END_OF_FILE.cpp testlib.h)
add_executable(WORD_SAME standard/WORD_SAME.cpp testlib.h)
add_executable(YES_NO standard/YES_NO.cpp testlib.h)
add_executable(INTEGER_SAME standard/INTEGER_SAME.cpp testlib.h)
add_executable(FLOAT_4 standard/FLOAT_4.cpp testlib.h)
add_executable(FLOAT_6 standard/FLOAT_6.cpp testlib.h)
