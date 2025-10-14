cmake_minimum_required(VERSION 3.28)
project(plaster)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(glfw3 3.3 REQUIRED)
find_package(bgfx REQUIRED)
find_package(Lua 5.4 REQUIRED)


add_library(plaster STATIC)

target_sources(plaster
   PRIVATE
      src/core/renderer.cpp
      src/core/ui_engine.cpp
      src/input/input_manager.cpp
      src/lua/lua_bindings.cpp)

target_include_directories(plaster
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${LUA_INCLUDE_DIR}
)

target_link_libraries(plaster
    PUBLIC
        glfw
        bgfx
        ${LUA_LIBRARIES}
)

install(
    DIRECTORY include/
    DESTINATION include
)

install(
    TARGETS plaster
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)
