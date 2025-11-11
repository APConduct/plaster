#!/bin/bash

# Cross-platform debug build script
# Supports macOS, Windows/MSYS2, and Linux

set -e  # Exit on any error

# Get project directory and name dynamically
PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_NAME="$(basename "$PROJECT_DIR")"

# Detect the operating system
detect_os() {
    case "$(uname -s)" in
        Darwin*)
            echo "macos"
            ;;
        MINGW*|MSYS*|CYGWIN*)
            echo "windows"
            ;;
        Linux*)
            echo "linux"
            ;;
        *)
            echo "unknown"
            ;;
    esac
}

OS="$(detect_os)"
echo "Detected OS: $OS"

# Clean previous build if it exists
if [ -d "./cmake-build-debug" ]; then
    echo "Cleaning previous build directory..."
    rm -rf ./cmake-build-debug
fi

echo "Building $PROJECT_NAME in Debug mode..."

# Set platform-specific variables
case "$OS" in
    "macos")
        echo "Configuring for macOS..."
        CMAKE_C_COMPILER="clang"
        CMAKE_CXX_COMPILER="clang++"
        CMAKE_GENERATOR="Ninja"
        CMAKE_MAKE_PROGRAM="ninja"

        # Check if we're using Homebrew LLVM
        if [ -n "$HOMEBREW_LLVM_LIBCXX" ] && [ -d "$HOMEBREW_LLVM_LIBCXX" ]; then
            CXX_FLAGS="-Wall -Wextra -Wshadow -Wpedantic -Wno-variadic-macros -isysroot $(xcrun --show-sdk-path)"
            LINKER_FLAGS="-L$HOMEBREW_LLVM_LIBCXX -Wl,-rpath,$HOMEBREW_LLVM_LIBCXX"
        else
            CXX_FLAGS="-Wall -Wextra -Wshadow -Wpedantic -Wno-variadic-macros -isysroot $(xcrun --show-sdk-path)"
            LINKER_FLAGS=""
        fi

        VCPKG_TRIPLET="x64-osx"
        BUILD_COMMAND="ninja -C ./cmake-build-debug"
        ;;

    "windows")
        echo "Configuring for Windows/MSYS2..."

        # Check if we should use MSYS2 packages + vcpkg hybrid approach
        USE_MSYS2_PACKAGES=false
        USE_HYBRID_APPROACH=false
        USE_FETCHCONTENT_BGFX=false

        # Check for MSYS2 packages
        if command -v pacman >/dev/null 2>&1; then
            echo "Checking for MSYS2 packages..."
            MISSING_PACKAGES=()

            # Check for required packages (excluding bgfx - not available in MSYS2)
            if ! pacman -Q mingw-w64-ucrt-x86_64-glfw >/dev/null 2>&1; then
                MISSING_PACKAGES+=("mingw-w64-ucrt-x86_64-glfw")
            fi
            if ! pacman -Q mingw-w64-ucrt-x86_64-lua >/dev/null 2>&1; then
                MISSING_PACKAGES+=("mingw-w64-ucrt-x86_64-lua")
            fi
            if ! pacman -Q mingw-w64-ucrt-x86_64-glm >/dev/null 2>&1; then
                MISSING_PACKAGES+=("mingw-w64-ucrt-x86_64-glm")
            fi
            if ! pacman -Q mingw-w64-ucrt-x86_64-raylib >/dev/null 2>&1; then
                MISSING_PACKAGES+=("mingw-w64-ucrt-x86_64-raylib")
            fi

            if [ ${#MISSING_PACKAGES[@]} -eq 0 ]; then
                # Check if bgfx is available via different methods
                if [ -n "$VCPKG_TOOLCHAIN" ] && [ -f "$VCPKG_TOOLCHAIN" ]; then
                    echo "✅ MSYS2 packages found! Using hybrid approach: MSYS2 + vcpkg for bgfx."
                    USE_HYBRID_APPROACH=true
                else
                    echo "✅ MSYS2 packages found! Will use FetchContent for bgfx."
                    USE_FETCHCONTENT_BGFX=true
                    USE_MSYS2_PACKAGES=true
                fi
            else
                echo "❓ Missing MSYS2 packages: ${MISSING_PACKAGES[*]}"
                echo "Install with: pacman -S ${MISSING_PACKAGES[*]}"
                echo "Falling back to full vcpkg..."
            fi
        fi

        if [ "$USE_HYBRID_APPROACH" = true ]; then
            # Use Clang + Ninja with hybrid approach (MSYS2 + vcpkg for bgfx only)
            echo "Using Clang + Ninja with hybrid approach (MSYS2 + vcpkg for bgfx)..."
            CMAKE_C_COMPILER="clang"
            CMAKE_CXX_COMPILER="clang++"
            CMAKE_GENERATOR="Ninja"
            CMAKE_MAKE_PROGRAM="ninja"
            CXX_FLAGS="-Wall -Wextra -Wpedantic -g -std=c++23"
            LINKER_FLAGS=""
            VCPKG_TRIPLET="x64-windows"
            BUILD_COMMAND="ninja -C ./cmake-build-debug"
        elif [ "$USE_MSYS2_PACKAGES" = true ]; then
            # Use Clang + Ninja with MSYS2 packages
            if [ "$USE_FETCHCONTENT_BGFX" = true ]; then
                echo "Using Clang + Ninja with MSYS2 packages + FetchContent for bgfx..."
            else
                echo "Using Clang + Ninja with MSYS2 packages (no bgfx)..."
            fi
            CMAKE_C_COMPILER="clang"
            CMAKE_CXX_COMPILER="clang++"
            CMAKE_GENERATOR="Ninja"
            CMAKE_MAKE_PROGRAM="ninja"
            CXX_FLAGS="-Wall -Wextra -Wpedantic -g -std=c++23"
            LINKER_FLAGS=""
            VCPKG_TRIPLET=""
            BUILD_COMMAND="ninja -C ./cmake-build-debug"
        else
            # Fallback to vcpkg with MSBuild
            echo "Using Visual Studio MSBuild (for vcpkg compatibility)..."

            # Check if we can use better compilers for the actual project
            if command -v clang >/dev/null 2>&1; then
                CMAKE_C_COMPILER="clang"
                CMAKE_CXX_COMPILER="clang++"
                CXX_FLAGS="-Wall -Wextra -Wpedantic -g -std=c++23"
                echo "  → Will use Clang for project compilation"
            else
                CMAKE_C_COMPILER=""
                CMAKE_CXX_COMPILER=""
                CXX_FLAGS=""
                echo "  → Will use MSVC for project compilation"
            fi

            CMAKE_GENERATOR="Visual Studio 17 2022"
            CMAKE_MAKE_PROGRAM=""
            LINKER_FLAGS=""
            VCPKG_TRIPLET="x64-windows"
            BUILD_COMMAND="cmake --build ./cmake-build-debug --config Debug --parallel"
        fi
        ;;

    "linux")
        echo "Configuring for Linux..."
        CMAKE_C_COMPILER="gcc"
        CMAKE_CXX_COMPILER="g++"
        CMAKE_GENERATOR="Ninja"
        CMAKE_MAKE_PROGRAM="ninja"
        CXX_FLAGS="-Wall -Wextra -Wpedantic -g"
        LINKER_FLAGS=""
        VCPKG_TRIPLET="x64-linux"
        BUILD_COMMAND="ninja -C ./cmake-build-debug"
        ;;

    *)
        echo "Unsupported operating system: $OS"
        exit 1
        ;;
esac

# Find vcpkg toolchain file
VCPKG_TOOLCHAIN=""
for path in \
    "$HOME/vcpkg/scripts/buildsystems/vcpkg.cmake" \
    "/c/msys64/home/aidan/vcpkg/scripts/buildsystems/vcpkg.cmake" \
    "/opt/vcpkg/scripts/buildsystems/vcpkg.cmake" \
    "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" \
    "$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" \
    ; do
    if [ -f "$path" ]; then
        VCPKG_TOOLCHAIN="$path"
        echo "Found vcpkg toolchain: $path"
        break
    fi
done

if [ -z "$VCPKG_TOOLCHAIN" ]; then
    echo "Warning: vcpkg toolchain file not found. Building without vcpkg..."
    echo "Searched in common locations. Set VCPKG_ROOT environment variable if needed."
fi

# Build CMake command
CMAKE_ARGS=(
    -DCMAKE_BUILD_TYPE=Debug
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
)

# Add compiler settings if specified
if [ -n "$CMAKE_C_COMPILER" ]; then
    CMAKE_ARGS+=(-DCMAKE_C_COMPILER="$CMAKE_C_COMPILER")
fi
if [ -n "$CMAKE_CXX_COMPILER" ]; then
    CMAKE_ARGS+=(-DCMAKE_CXX_COMPILER="$CMAKE_CXX_COMPILER")
fi
if [ -n "$CMAKE_MAKE_PROGRAM" ]; then
    CMAKE_ARGS+=(-DCMAKE_MAKE_PROGRAM="$CMAKE_MAKE_PROGRAM")
fi

# Add flags if specified
if [ -n "$CXX_FLAGS" ]; then
    CMAKE_ARGS+=(-DCMAKE_CXX_FLAGS="$CXX_FLAGS")
fi
if [ -n "$LINKER_FLAGS" ]; then
    CMAKE_ARGS+=(-DCMAKE_EXE_LINKER_FLAGS="$LINKER_FLAGS")
fi

# Add vcpkg settings based on approach
if [ "$USE_HYBRID_APPROACH" = true ]; then
    echo "Using hybrid approach: MSYS2 packages + vcpkg for bgfx"
    CMAKE_ARGS+=(-DCMAKE_TOOLCHAIN_FILE="$VCPKG_TOOLCHAIN")
    CMAKE_ARGS+=(-DVCPKG_TARGET_TRIPLET="$VCPKG_TRIPLET")
    CMAKE_ARGS+=(-DUSE_HYBRID_PACKAGES=ON)
elif [ -n "$VCPKG_TOOLCHAIN" ] && [ "$USE_MSYS2_PACKAGES" != true ]; then
    CMAKE_ARGS+=(-DCMAKE_TOOLCHAIN_FILE="$VCPKG_TOOLCHAIN")
    CMAKE_ARGS+=(-DVCPKG_TARGET_TRIPLET="$VCPKG_TRIPLET")
elif [ "$USE_MSYS2_PACKAGES" = true ]; then
    if [ "$USE_FETCHCONTENT_BGFX" = true ]; then
        echo "Using MSYS2 packages + FetchContent for bgfx - skipping vcpkg"
        CMAKE_ARGS+=(-DUSE_FETCHCONTENT_BGFX=ON)
    else
        echo "Using MSYS2 packages only - skipping vcpkg"
    fi
fi

# Add generator
CMAKE_ARGS+=(-G "$CMAKE_GENERATOR")

# Add source and build directories
CMAKE_ARGS+=(-S . -B ./cmake-build-debug)

# Windows-specific environment adjustments
if [ "$OS" = "windows" ]; then
    if [ "$USE_MSYS2_PACKAGES" = true ] || [ "$USE_HYBRID_APPROACH" = true ] || [ "$USE_FETCHCONTENT_BGFX" = true ]; then
        echo "Setting up MSYS2 environment..."
        export PATH="/ucrt64/bin:$PATH"
        export PKG_CONFIG_PATH="/ucrt64/lib/pkgconfig:/ucrt64/share/pkgconfig"

        if [ "$USE_HYBRID_APPROACH" = true ]; then
            echo "  → Will also use vcpkg for bgfx"
        elif [ "$USE_FETCHCONTENT_BGFX" = true ]; then
            echo "  → Will use FetchContent for bgfx"
        fi
    else
        echo "Setting up Visual Studio environment..."
        # Set up Visual Studio environment variables for better compatibility
        export VCINSTALLDIR="/c/Program Files/Microsoft Visual Studio/2022/Community/VC/"
        export WindowsSdkDir="/c/Program Files (x86)/Windows Kits/10/"
    fi
fi

# Windows-specific generator platform
if [ "$OS" = "windows" ] && [ "$CMAKE_GENERATOR" = "Visual Studio 17 2022" ]; then
    CMAKE_ARGS+=(-DCMAKE_GENERATOR_PLATFORM=x64)
fi

echo "Running CMake configuration..."
echo "Command: cmake ${CMAKE_ARGS[*]}"

# Run CMake configuration
cmake "${CMAKE_ARGS[@]}"

# Check if cmake configuration succeeded
if [ $? -ne 0 ]; then
    echo "CMake configuration failed!"
    if [ "$OS" = "windows" ]; then
        echo ""
        if [ "$USE_HYBRID_APPROACH" = true ]; then
            echo "Using hybrid approach - ensure dependencies are available:"
            echo "MSYS2 packages:"
            echo "  pacman -S mingw-w64-ucrt-x86_64-glfw mingw-w64-ucrt-x86_64-lua mingw-w64-ucrt-x86_64-glm mingw-w64-ucrt-x86_64-raylib"
            echo "vcpkg packages:"
            echo "  vcpkg install bgfx:x64-windows"
        elif [ "$USE_MSYS2_PACKAGES" = true ]; then
            echo "If using MSYS2 packages, make sure all packages are installed:"
            echo "  pacman -S mingw-w64-ucrt-x86_64-glfw"
            echo "  pacman -S mingw-w64-ucrt-x86_64-lua"
            echo "  pacman -S mingw-w64-ucrt-x86_64-glm"
            echo "  pacman -S mingw-w64-ucrt-x86_64-raylib"
            echo ""
            echo "For bgfx, you can either:"
            echo "  1. Use FetchContent (automatic download, recommended)"
            echo "  2. Build from source, or"
            echo "  3. Use vcpkg (may have RC.exe issues)"
        else
            echo "If packages fail to install, try installing them manually:"
            echo "  vcpkg install glfw3:x64-windows"
            echo "  vcpkg install bgfx:x64-windows"
            echo "  vcpkg install lua:x64-windows"
            echo "  vcpkg install glm:x64-windows"
            echo "  vcpkg install raylib:x64-windows"
            echo ""
            echo "Or switch to MSYS2 + FetchContent by installing:"
            echo "  pacman -S mingw-w64-ucrt-x86_64-glfw mingw-w64-ucrt-x86_64-lua mingw-w64-ucrt-x86_64-glm mingw-w64-ucrt-x86_64-raylib"
            echo "  (bgfx will be downloaded automatically with FetchContent)"
            echo "Or use vcpkg:"
            echo "  vcpkg install bgfx:x64-windows"
        fi
    fi
    exit 1
fi

# Build the project
echo "Building with: $BUILD_COMMAND"
eval "$BUILD_COMMAND"

# Check if build succeeded
if [ $? -eq 0 ]; then
    echo "Build successful!"

    # Create compile_commands.json symlink if it exists
    if [ -f "./cmake-build-debug/compile_commands.json" ]; then
        if [ "$OS" = "windows" ]; then
            # Copy file on Windows since symlinks don't work reliably
            if cp "./cmake-build-debug/compile_commands.json" . 2>/dev/null; then
                echo "Copied compile_commands.json to project root"
            else
                echo "Warning: Could not copy compile_commands.json"
            fi
        else
            # Use symlink on Unix-like systems
            ln -sf "./cmake-build-debug/compile_commands.json" .
            echo "Created compile_commands.json symlink"
        fi
    fi

    echo ""
    echo "✅ Debug build completed successfully!"
    echo "📁 Build output: ./cmake-build-debug/"

    # Platform-specific executable info and post-build options
    case "$OS" in
        "windows")
            if [ "$USE_HYBRID_APPROACH" = true ]; then
                echo "🎯 Executables: ./cmake-build-debug/*.exe"
                echo "🔧 Built with: Clang + Ninja + MSYS2 + vcpkg (hybrid)"
                echo ""
                echo "💡 For faster rebuilds:"
                echo "   ninja -C ./cmake-build-debug"
            elif [ "$USE_MSYS2_PACKAGES" = true ]; then
                echo "🎯 Executables: ./cmake-build-debug/*.exe"
                if [ "$USE_FETCHCONTENT_BGFX" = true ]; then
                    echo "🔧 Built with: Clang + Ninja + MSYS2 packages + FetchContent bgfx"
                else
                    echo "🔧 Built with: Clang + Ninja + MSYS2 packages"
                fi
                echo ""
                echo "💡 For faster rebuilds:"
                echo "   ninja -C ./cmake-build-debug"
            else
                echo "🎯 Executables: ./cmake-build-debug/Debug/*.exe"
                echo "🔧 Built with: MSBuild + vcpkg"

                # Offer Ninja rebuild option if available
                if command -v ninja >/dev/null 2>&1 && [ -n "$CMAKE_C_COMPILER" ] && [ "$CMAKE_C_COMPILER" = "clang" ]; then
                    echo ""
                    echo "💡 For faster rebuilds, you can now use:"
                    echo "   ninja -C ./cmake-build-debug"
                    echo "   (vcpkg dependencies are already built with MSBuild)"
                fi
            fi
            ;;
        *)
            echo "🎯 Executables: ./cmake-build-debug/*"
            ;;
    esac
else
    echo "❌ Build failed!"
    exit 1
fi
