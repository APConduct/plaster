project(plaster_externals)

add_library(glad_gl STATIC
        glad/include/glad/gl.h
        glad/src/gl.c
)

target_include_directories(glad_gl INTERFACE
        glad/include
)

set(glad_gl_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/glad/include)

message(
        STATUS "glad_gl found: ${glad_gl_FOUND}" " at: ${glad_gl_INCLUDE_DIR}"
)