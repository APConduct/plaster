cmake_minimum_required(VERSION 3.28)
project(plaster)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Try to find packages - handle both vcpkg and MSYS2 scenarios
find_package(glfw3 3.3 QUIET)
find_package(bgfx QUIET)
find_package(Lua 5.4 QUIET)

# If packages not found via CMake, try pkg-config (MSYS2)
if(NOT glfw3_FOUND)
    find_package(PkgConfig QUIET)
    if(PkgConfig_FOUND)
        pkg_check_modules(GLFW3 QUIET glfw3)
    endif()
endif()

if(NOT Lua_FOUND)
    find_package(PkgConfig QUIET)
    if(PkgConfig_FOUND)
        pkg_check_modules(LUA QUIET lua5.4)
        if(NOT LUA_FOUND)
            pkg_check_modules(LUA QUIET lua)
        endif()
    endif()
endif()

# GLM is header-only, try to find it
find_package(glm QUIET)
if(NOT glm_FOUND)
    find_package(PkgConfig QUIET)
    if(PkgConfig_FOUND)
        pkg_check_modules(GLM QUIET glm)
    endif()
endif()

# Raylib
find_package(raylib QUIET)
if(NOT raylib_FOUND)
    find_package(PkgConfig QUIET)
    if(PkgConfig_FOUND)
        pkg_check_modules(RAYLIB QUIET raylib)
    endif()
endif()

# Handle bgfx with FetchContent if enabled
if(USE_FETCHCONTENT_BGFX)
    message(STATUS "Using FetchContent to download and build bgfx...")

    include(FetchContent)

    # Fetch bgfx
    FetchContent_Declare(
        bgfx
        GIT_REPOSITORY https://github.com/bkaradzic/bgfx.git
        GIT_TAG master  # You can specify a specific tag/commit for stability
        GIT_SHALLOW TRUE
    )

    # Set bgfx options before fetching
    set(BGFX_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BGFX_BUILD_TOOLS OFF CACHE BOOL "" FORCE)
    set(BGFX_INSTALL OFF CACHE BOOL "" FORCE)

    FetchContent_MakeAvailable(bgfx)
    set(bgfx_FOUND TRUE)

    message(STATUS "bgfx downloaded and configured via FetchContent")
endif()

add_library(plaster STATIC)

target_sources(plaster
   PRIVATE
      src/core/renderer.cpp
      src/core/ui_engine.cpp
      src/input/input_manager.cpp
      src/lua/lua_bindings.cpp
      src/input/input_manager.cpp
      PUBLIC
      FILE_SET CXX_MODULES
      FILES
      include/modules/point.ixx
      include/modules/plaster/renderer.ixx
      include/modules/plaster/ui_engine.ixx
      include/modules/plaster/input_manager.ixx
      include/modules/plaster/lua_api.ixx
      include/modules/plaster/context.ixx
      include/modules/plaster/ui_engine_context.ixx
)

target_sources(plaster
    PUBLIC
        FILE_SET CXX_MODULES
        FILES
        include/modules/flat/point.ixx
        include/modules/flat/size.ixx
        include/modules/flat/flat.ixx
        include/modules/plaster.ixx
        include/modules/lua.ixx
        include/modules/renderer.ixx)

target_include_directories(plaster
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Add include directories based on what we found
if(Lua_FOUND)
    target_include_directories(plaster PRIVATE ${LUA_INCLUDE_DIR})
elseif(LUA_FOUND)
    target_include_directories(plaster PRIVATE ${LUA_INCLUDE_DIRS})
endif()

if(GLFW3_FOUND)
    target_include_directories(plaster PRIVATE ${GLFW3_INCLUDE_DIRS})
endif()

if(GLM_FOUND)
    target_include_directories(plaster PRIVATE ${GLM_INCLUDE_DIRS})
endif()

if(RAYLIB_FOUND)
    target_include_directories(plaster PRIVATE ${RAYLIB_INCLUDE_DIRS})
endif()

# Add bgfx include directories when using FetchContent
if(USE_FETCHCONTENT_BGFX AND bgfx_FOUND)
    target_include_directories(plaster PRIVATE ${bgfx_SOURCE_DIR}/include)
endif()

# Link libraries based on what we found
set(PLASTER_LIBS "")

# GLFW3
if(glfw3_FOUND)
    list(APPEND PLASTER_LIBS glfw)
elseif(GLFW3_FOUND)
    list(APPEND PLASTER_LIBS ${GLFW3_LIBRARIES})
    target_link_directories(plaster PUBLIC ${GLFW3_LIBRARY_DIRS})
else()
    message(WARNING "GLFW3 not found - you may need to install it")
endif()

# bgfx (available through vcpkg or FetchContent)
if(bgfx_FOUND OR USE_FETCHCONTENT_BGFX)
    target_include_directories(plaster PRIVATE ${bgfx_SOURCE_DIR}/include)
    if(USE_FETCHCONTENT_BGFX)
        list(APPEND PLASTER_LIBS bgfx)
        message(STATUS "Using bgfx from FetchContent")
    elseif(bgfx_FOUND)
        list(APPEND PLASTER_LIBS bgfx)
        message(STATUS "Using bgfx from vcpkg/system")
    endif()
else()
    if(USE_FETCHCONTENT_BGFX)
        message(WARNING "FetchContent bgfx failed - check network connection and git availability")
    else()
        message(WARNING "bgfx not found - you may need to build it from source, use vcpkg, or enable FetchContent")
    endif()
endif()

# Lua
if(Lua_FOUND)
    list(APPEND PLASTER_LIBS ${LUA_LIBRARIES})
elseif(LUA_FOUND)
    list(APPEND PLASTER_LIBS ${LUA_LIBRARIES})
    target_link_directories(plaster PUBLIC ${LUA_LIBRARY_DIRS})
else()
    message(WARNING "Lua not found - you may need to install it")
endif()

# GLM is header-only, no linking needed

# Raylib
if(raylib_FOUND)
    list(APPEND PLASTER_LIBS raylib)
elseif(RAYLIB_FOUND)
    list(APPEND PLASTER_LIBS ${RAYLIB_LIBRARIES})
    target_link_directories(plaster PUBLIC ${RAYLIB_LIBRARY_DIRS})
else()
    message(WARNING "raylib not found - you may need to install it")
endif()

target_link_libraries(plaster
    PUBLIC
        ${PLASTER_LIBS}
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
