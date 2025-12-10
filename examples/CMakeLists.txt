# Option to toggle examples
option(BUILD_EXAMPLES "Build example executables" ON)

if(NOT BUILD_EXAMPLES)
    message(STATUS "Examples are disabled (BUILD_EXAMPLES=OFF)")
    return()
endif()

# Basic example
add_executable(basic_example)

target_sources(basic_example
    PRIVATE
        basic_example/main.cpp
)

# Inherit C++ standard from plaster via INTERFACE compile features
target_link_libraries(basic_example PRIVATE plaster)

# Put example binaries in a predictable folder under the build tree
set_target_properties(basic_example PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples"
)

# Optional: organize in IDEs
if(MSVC OR CMAKE_GENERATOR MATCHES "Xcode")
    set_property(TARGET basic_example PROPERTY FOLDER "examples")
endif()
