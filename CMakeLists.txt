cmake_minimum_required(VERSION 3.10)

project(my_shared_ptr VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)

add_executable(my_shared_ptr main.cpp shared_ptr.h)