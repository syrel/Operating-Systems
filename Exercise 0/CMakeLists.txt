cmake_minimum_required(VERSION 3.6)
project(_OS__Exercise_0)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/multiply.h src/results.h src/multiply.c)
add_executable(_OS__Exercise_0 ${SOURCE_FILES})