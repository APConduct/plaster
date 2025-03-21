project(plaster_lib)

add_library(plaster STATIC
        library.h library.cpp
)


target_sources(plaster
        PUBLIC
        FILE_SET CXX_MODULES
        FILES
        mod/core.ixx
        mod/window.ixx
        mod/event.ixx
        mod/renderer.ixx

)

target_link_libraries(plaster PUBLIC
        glad
        glfw

        glm::glm
)

target_include_directories(
        plaster
        PUBLIC
        ${glad_SOURCE_DIR}/include
)




