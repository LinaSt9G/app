# CMake Version
cmake_minimum_required(VERSION 3.18)

# Project name & Language
project(bluetoothcommunication CXX)

# Find pkg-config first
find_package(PkgConfig REQUIRED)

# Use pkg-config to get hints for bluetooth locations
pkg_check_modules(BLUEZ REQUIRED bluez)

# Include bluetooth headers
include_directories(${BLUEZ_INCLUDE_DIRS})


find_package(Threads REQUIRED)

# source file & generated file
add_executable(main main.cc)


# Link with bluetooth libraries
target_link_libraries(main ${BLUEZ_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

# Additional linker flags if necessary
target_link_options(main PUBLIC ${BLUEZ_LDFLAGS_OTHER})