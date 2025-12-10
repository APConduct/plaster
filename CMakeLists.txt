cmake_minimum_required(VERSION 3.28)
project(plaster)

# Language standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 1) Create the target first, then configure it
add_library(plaster STATIC)
# Ensure consumers inherit the minimum C++23 standard
target_compile_features(plaster INTERFACE cxx_std_23)

# 2) Add sources/modules
target_sources(plaster
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
        include/modules/flat/point.ixx
        include/modules/plaster/renderer.ixx
        include/modules/plaster/ui_engine.ixx
        include/modules/plaster/input_manager.ixx
        include/modules/plaster/lua_api.ixx
        include/modules/plaster/context.ixx
        include/modules/plaster/ui_engine_context.ixx
        include/modules/flat/size.ixx
        include/modules/flat/flat.ixx
        include/modules/plaster.ixx
)

# 3) Base include directories
target_include_directories(plaster
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# 4) Discover packages - prefer vcpkg CONFIG packages
#    These will define imported targets that propagate include/link dirs.
find_package(glfw3 CONFIG QUIET)
find_package(bgfx CONFIG QUIET)
find_package(Lua 5.4 QUIET)      # Module-mode finder; provides LUA_* variables
find_package(glm CONFIG QUIET)
find_package(raylib CONFIG QUIET)

# 5) Fallback to PkgConfig for MSYS2 when CONFIG/module packages aren't found
#    We only initialize pkg-config once if any dependency is missing.
set(_need_pkgconfig OFF)
if(NOT glfw3_FOUND OR NOT Lua_FOUND OR NOT glm_FOUND OR NOT raylib_FOUND)
    find_package(PkgConfig QUIET)
    if(PkgConfig_FOUND)
        set(_need_pkgconfig ON)
    endif()
endif()

if(_need_pkgconfig AND NOT glfw3_FOUND)
    pkg_check_modules(GLFW3 QUIET glfw3)
endif()

if(_need_pkgconfig AND NOT Lua_FOUND)
    pkg_check_modules(LUA QUIET lua5.4)
    if(NOT LUA_FOUND)
        pkg_check_modules(LUA QUIET lua)
    endif()
endif()

if(_need_pkgconfig AND NOT glm_FOUND)
    pkg_check_modules(GLM QUIET glm)
endif()

if(_need_pkgconfig AND NOT raylib_FOUND)
    pkg_check_modules(RAYLIB QUIET raylib)
endif()

# 6) bgfx: allow explicit FetchContent, prefer vcpkg when available, and fallback to FetchContent
if(USE_FETCHCONTENT_BGFX)
    message(STATUS "Using bgfx via FetchContent (forced)")
    include(FetchContent)
    FetchContent_Declare(
        bgfx
        GIT_REPOSITORY https://github.com/bkaradzic/bgfx.git
        GIT_TAG master
        GIT_SHALLOW TRUE
    )
    set(BGFX_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BGFX_BUILD_TOOLS OFF CACHE BOOL "" FORCE)
    set(BGFX_INSTALL OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(bgfx)

    # FetchContent build typically exposes a target named 'bgfx'
    target_include_directories(plaster PRIVATE ${bgfx_SOURCE_DIR}/include)
    target_link_libraries(plaster PUBLIC bgfx)

elseif(bgfx_FOUND)
    message(STATUS "Using bgfx from vcpkg/system")
    # Link the exported target so CMake propagates include/link dirs
    target_link_libraries(plaster PUBLIC bgfx::bgfx)

else()
    message(STATUS "bgfx not found via CMake/vcpkg - falling back to FetchContent")
    include(FetchContent)
    FetchContent_Declare(
        bgfx
        GIT_REPOSITORY https://github.com/bkaradzic/bgfx.git
        GIT_TAG master
        GIT_SHALLOW TRUE
    )
    set(BGFX_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BGFX_BUILD_TOOLS OFF CACHE BOOL "" FORCE)
    set(BGFX_INSTALL OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(bgfx)

    target_include_directories(plaster PRIVATE ${bgfx_SOURCE_DIR}/include)
    target_link_libraries(plaster PUBLIC bgfx)
endif()

# 7) Link other dependencies with preference for imported targets; fall back to pkg-config variables.

# GLFW3
if(glfw3_FOUND)
    # vcpkg exports target 'glfw' for CONFIG mode
    target_link_libraries(plaster PUBLIC glfw)
elseif(GLFW3_FOUND) # PkgConfig fallback
    target_include_directories(plaster PRIVATE ${GLFW3_INCLUDE_DIRS})
    if(GLFW3_LIBRARY_DIRS)
        target_link_directories(plaster PUBLIC ${GLFW3_LIBRARY_DIRS})
    endif()
    target_link_libraries(plaster PUBLIC ${GLFW3_LIBRARIES})
else()
    message(WARNING "GLFW3 not found - you may need to install it")
endif()

# Lua
if(Lua_FOUND) # CMake module-mode find_package(Lua)
    target_include_directories(plaster PRIVATE ${LUA_INCLUDE_DIR})
    target_link_libraries(plaster PUBLIC ${LUA_LIBRARIES})
elseif(LUA_FOUND) # PkgConfig fallback
    target_include_directories(plaster PRIVATE ${LUA_INCLUDE_DIRS})
    if(LUA_LIBRARY_DIRS)
        target_link_directories(plaster PUBLIC ${LUA_LIBRARY_DIRS})
    endif()
    target_link_libraries(plaster PUBLIC ${LUA_LIBRARIES})
else()
    message(WARNING "Lua not found - you may need to install it")
endif()

# GLM (header-only)
if(glm_FOUND) # vcpkg CONFIG mode
    target_link_libraries(plaster PUBLIC glm::glm)
elseif(GLM_FOUND) # PkgConfig fallback
    target_include_directories(plaster PRIVATE ${GLM_INCLUDE_DIRS})
else()
    message(WARNING "GLM not found - you may need to install it")
endif()

# Raylib
if(raylib_FOUND)
    target_link_libraries(plaster PUBLIC raylib)
elseif(RAYLIB_FOUND) # PkgConfig fallback
    target_include_directories(plaster PRIVATE ${RAYLIB_INCLUDE_DIRS})
    if(RAYLIB_LIBRARY_DIRS)
        target_link_directories(plaster PUBLIC ${RAYLIB_LIBRARY_DIRS})
    endif()
    target_link_libraries(plaster PUBLIC ${RAYLIB_LIBRARIES})
else()
    message(WARNING "raylib not found - you may need to install it")
endif()

# 8) Examples
add_subdirectory(examples)

# 9) Install rules
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
