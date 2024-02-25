# CMake Version
cmake_minimum_required(VERSION 3.18)

# Project name & Language
project(tcpipcommunication CXX)


find_package(Threads REQUIRED)


# source file & generated file
add_executable(main main.cc)


target_link_libraries(main ${CMAKE_THREAD_LIBS_INIT})