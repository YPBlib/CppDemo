cmake_minimum_required(VERSION 3.8)
project(draft)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES draft.cpp try.h)
add_executable(draft ${SOURCE_FILES})