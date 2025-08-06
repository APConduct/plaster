project(glad_gl)

add_library(
        glad_gl STATIC
        glad/src/gl.c
        glad/include/glad/gl.h
)

set(glad_gl_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/glad/include PARENT_SCOPE)

target_include_directories(
        glad_gl
        PUBLIC
        glad/include
)