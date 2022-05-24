cmake_minimum_required(VERSION 3.16)


set(PROJECT_NAME library)

project(${PROJECT_NAME} C CXX)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES sources/mt.h
        sources/errors.h
        sources/mt_tbb.h
        sources/vector.h
        sources/matrix.h
        test/main.cpp)

#set(test test/ex.cpp)


add_library(la-library SHARED sources/vector.h sources/matrix.h sources/errors.h sources/empty.cpp sources/mt.h
        sources/mt_tbb.h)
add_executable(${PROJECT_NAME} test/main.cpp ${INCLUDES} ${SOURCES})

find_package(TBB REQUIRED)
#find_package(GTest REQUIRED)
#find_package (Eigen3 3.3 REQUIRED NO_MODULE)

target_link_libraries(${PROJECT_NAME} TBB::tbb)
#target_link_libraries(${PROJECT_NAME} Eigen3::Eigen)
#target_link_libraries(${PROJECT_NAME} GTest::GTest)