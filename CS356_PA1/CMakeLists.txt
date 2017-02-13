cmake_minimum_required(VERSION 3.6)
project(CS356_PA1)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp BlockCipher.cpp BlockCipher.h)
add_executable(CS356_PA1 ${SOURCE_FILES})