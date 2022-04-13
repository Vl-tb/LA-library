cmake_minimum_required(VERSION 3.20)
project(la-library)

set(CMAKE_CXX_STANDARD 17)

add_library(la-library SHARED includes/vector.h includes/matrix.h)
add_executable(test main.cpp)