cmake_minimum_required(VERSION 3.20)
project(testing)

set(CMAKE_CXX_STANDARD 17)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

add_executable(main main.cpp)
target_link_libraries (main Eigen3::Eigen)


