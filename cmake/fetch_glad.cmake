include(FetchContent)


FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG v2.0.4
)
FetchContent_MakeAvailable(
        glad
)