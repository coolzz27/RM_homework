cmake_minimum_required(VERSION 3.10)
project(demo)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV 4 REQUIRED)

add_executable(demo ex2/ex2.cpp ex2/VO.cpp)
target_link_libraries(demo ${OpenCV_LIBS})
