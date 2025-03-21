cmake_minimum_required(VERSION 3.30)
project(plaster)

set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# specify whether to build with dependency location checkpoints
option(PLASTER_ENABLE_MARCO_POLO "Build with walktrough" ON)

# Build options
option(PLASTER_BUILD_EXAMPLES "Build the examples" ON)
option(PLASTER_BUILD_TESTS "Build the tests" ON)


include(cmake/fetch_glad.cmake)
include(cmake/fetch_glfw.cmake)

include(FetchContent)

find_package(
        glm REQUIRED
)

if (NOT glm_FOUND)
    FetchContent_Declare(
            glm
            GIT_REPOSITORY https://github.com/g-truc/glm.git
            GIT_TAG 1.0.1
    )
    FetchContent_MakeAvailable(glm)
endif ()

if (PLASTER_ENABLE_MARCO_POLO)
    message(
            STATUS "glm found: ${glm_FOUND}" " at: ${glm_DIR}"
    )
endif ()



add_subdirectory(src)
add_subdirectory(examples)

set(CMAKE_CXX_STANDARD 20)
