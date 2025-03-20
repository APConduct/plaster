project(plaster_lib)

add_library(plaster STATIC
        library.h library.cpp

)


target_sources(plaster
        PUBLIC
        FILE_SET CXX_MODULES
        FILES
        mod/core.ixx
)

target_link_libraries(plaster PUBLIC
        glfw
        glad

)




