cmake_minimum_required(VERSION 3.20)
project(la-library)

set(CMAKE_CXX_STANDARD 17)

add_library(la-library SHARED library.cpp)
