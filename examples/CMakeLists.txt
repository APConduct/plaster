add_executable(basic_example)

target_sources(basic_example
   PRIVATE basic_example/main.cpp)

target_link_libraries(basic_example PRIVATE
    plaster)
