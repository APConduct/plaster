cmake_minimum_required(VERSION 3.30)
project(plaster)

set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Build options
option(PLASTER_BUILD_EXAMPLES "Build the examples" ON)
option(PLASTER_BUILD_TESTS "Build the tests" ON)




add_subdirectory(src)
add_subdirectory(examples)

set(CMAKE_CXX_STANDARD 20)
