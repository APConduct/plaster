include(FetchContent)




FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG v2.0.8
)

set(GLAD_API "gl=4.6" CACHE STRING "API type/version pairs, like \"gl=4.6,gles=\", no version means latest")
set(GLAD_PROFILE "core" CACHE STRING "OpenGL Profile")
set(GLAD_GENERATOR "c" CACHE STRING "Language to generate the bindings for")
set(GLAD_INSTALL ON)

FetchContent_MakeAvailable(
        glad
)

message(
        STATUS "glad found: ${glad_FOUND}" " at: ${glad_SOURCE_DIR}"
)