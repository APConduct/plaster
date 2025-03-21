

 FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG ${GLFW_VERSION}
        GIT_SHALLOW ON    # Only fetch the specified tag
        GIT_PROGRESS ON   # Show progress during download
)

# Configure GLFW build options
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# Make GLFW available
FetchContent_MakeAvailable(glfw)