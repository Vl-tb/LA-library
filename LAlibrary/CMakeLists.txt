cmake_minimum_required(VERSION 3.16)


set(PROJECT_NAME test)

project(${PROJECT_NAME} C CXX)

set(CMAKE_CXX_STANDARD 17)

set(INCLUDES includes/mt.h
        includes/errors.h
        includes/mt_tbb.h
        includes/vector.h
        includes/matrix.h)

set(SOURCES sources/ex.cpp)


add_library(la-library SHARED includes/vector.h includes/matrix.h includes/errors.h sources/ex.cpp includes/mt.h
        includes/mt_tbb.h)
add_executable(${PROJECT_NAME} sources/main.cpp ${INCLUDES} ${SOURCES})

find_package(TBB REQUIRED)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

target_link_libraries(${PROJECT_NAME} TBB::tbb)
target_link_libraries (${PROJECT_NAME} Eigen3::Eigen)