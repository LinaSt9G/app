# CMake Version
cmake_minimum_required(VERSION 3.22)
# Project name & Language
project(searchTablePeformanceEXP CXX)

# compile option
add_compile_options(-O3)

# For Auto generate source code
add_executable(createTestData createTestData.cc)

# custom cmake commannd
add_custom_target(runCreateTestData ALL
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/createTestData
    COMMENT "Running createTestData..."
)
# Execute createTestData to generate source code
add_dependencies(runCreateTestData createTestData)

# main app compile
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/autogen/)
include_directories("${INCLUDE_DIR}")
add_executable(main main.cc)
