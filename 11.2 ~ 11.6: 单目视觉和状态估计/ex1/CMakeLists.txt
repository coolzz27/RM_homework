cmake_minimum_required(VERSION 3.10)
project(demo)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV 4 REQUIRED)

add_executable(demo main.cpp)
target_link_libraries(demo ${OpenCV_LIBS})
