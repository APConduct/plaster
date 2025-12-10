# Assets.cmake
#
# Helper utilities to copy asset files/directories alongside built targets
# so running executables from the build tree can find their resources.
#
# Usage:
#   include(${CMAKE_SOURCE_DIR}/cmake/Assets.cmake)
#
#   plaster_add_assets(
#       TARGET my_app
#       ASSETS_DIR ${CMAKE_SOURCE_DIR}/assets
#       OUTPUT_DIR ${CMAKE_BINARY_DIR}/examples
#       # Optional:
#       # PATTERN "*.png;*.jpg;*.json"      # Copy only certain files
#       # EXCLUDE  "*/tmp/*;*.psd"          # Exclude patterns
#       # CLEAN_BEFORE_COPY ON              # Remove OUTPUT_DIR before copying
#   )
#
# Notes:
# - Copies occur on each build via a POST_BUILD step.
# - By default, copies entire ASSETS_DIR recursively to OUTPUT_DIR/TARGET_NAME_assets.
# - You can override the default destination via OUTPUT_DIR.
# - Patterns are semicolon-separated GLOBs matched relative to ASSETS_DIR.
# - Excludes apply after includes; if no PATTERN is specified, all files are included.
# - CLEAN_BEFORE_COPY deletes the destination dir before copying (careful).
#
# Tested on macOS, Windows (Ninja/MSVC), and Linux.

function(plaster_add_assets)
    set(options CLEAN_BEFORE_COPY)
    set(oneValueArgs TARGET ASSETS_DIR OUTPUT_DIR)
    set(multiValueArgs PATTERN EXCLUDE)
    cmake_parse_arguments(PAA "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT PAA_TARGET)
        message(FATAL_ERROR "plaster_add_assets: TARGET is required")
    endif()
    if(NOT TARGET ${PAA_TARGET})
        message(FATAL_ERROR "plaster_add_assets: target '${PAA_TARGET}' does not exist")
    endif()

    if(NOT PAA_ASSETS_DIR)
        message(FATAL_ERROR "plaster_add_assets: ASSETS_DIR is required")
    endif()
    if(NOT IS_DIRECTORY "${PAA_ASSETS_DIR}")
        message(FATAL_ERROR "plaster_add_assets: ASSETS_DIR '${PAA_ASSETS_DIR}' is not a directory")
    endif()

    # Default output directory: <binary_dir>/<target>_assets
    if(NOT PAA_OUTPUT_DIR)
        set(PAA_OUTPUT_DIR "${CMAKE_BINARY_DIR}/${PAA_TARGET}_assets")
    endif()

    # Normalize patterns to lists
    set(include_patterns "${PAA_PATTERN}")
    set(exclude_patterns "${PAA_EXCLUDE}")

    # Build up copy commands
    set(copy_script "")
    # Optional clean before copy
    if(PAA_CLEAN_BEFORE_COPY)
        string(APPEND copy_script "if(EXISTS \"$<SHELL_PATH:${PAA_OUTPUT_DIR}>\")\n")
        string(APPEND copy_script "  file(REMOVE_RECURSE \"$<SHELL_PATH:${PAA_OUTPUT_DIR}>\")\n")
        string(APPEND copy_script "endif()\n")
    endif()
    string(APPEND copy_script "file(MAKE_DIRECTORY \"$<SHELL_PATH:${PAA_OUTPUT_DIR}>\")\n")

    # If PATTERN specified, do selective globbing; else copy directory recursively.
    if(include_patterns)
        # Glob with patterns relative to ASSETS_DIR
        string(APPEND copy_script "set(_src_dir \"$<SHELL_PATH:${PAA_ASSETS_DIR}>\")\n")
        string(APPEND copy_script "set(_dst_dir \"$<SHELL_PATH:${PAA_OUTPUT_DIR}>\")\n")
        string(APPEND copy_script "set(_include_patterns ${include_patterns})\n")
        string(APPEND copy_script "set(_exclude_patterns ${exclude_patterns})\n")
        string(APPEND copy_script "set(_files)\n")
        string(APPEND copy_script "foreach(_pat IN LISTS _include_patterns)\n")
        string(APPEND copy_script "  file(GLOB_RECURSE _matched \"${_src_dir}/${_pat}\")\n")
        string(APPEND copy_script "  list(APPEND _files ${_matched})\n")
        string(APPEND copy_script "endforeach()\n")
        # Apply excludes
        string(APPEND copy_script "foreach(_ex IN LISTS _exclude_patterns)\n")
        string(APPEND copy_script "  if(_ex)\n")
        string(APPEND copy_script "    list(FILTER _files EXCLUDE REGEX \"${_ex}\")\n")
        string(APPEND copy_script "  endif()\n")
        string(APPEND copy_script "endforeach()\n")
        # Copy preserving relative layout
        string(APPEND copy_script "foreach(_f IN LISTS _files)\n")
        string(APPEND copy_script "  file(RELATIVE_PATH _rel \"${_src_dir}\" \"${_f}\")\n")
        string(APPEND copy_script "  get_filename_component(_dst_subdir \"${_rel}\" DIRECTORY)\n")
        string(APPEND copy_script "  if(_dst_subdir)\n")
        string(APPEND copy_script "    file(MAKE_DIRECTORY \"${_dst_dir}/${_dst_subdir}\")\n")
        string(APPEND copy_script "  endif()\n")
        string(APPEND copy_script "  file(COPY \"${_f}\" DESTINATION \"${_dst_dir}/${_dst_subdir}\")\n")
        string(APPEND copy_script "endforeach()\n")
    else()
        # Copy entire directory recursively
        string(APPEND copy_script "file(COPY \"$<SHELL_PATH:${PAA_ASSETS_DIR}>\" DESTINATION \"$<SHELL_PATH:${PAA_OUTPUT_DIR}>\")\n")
    endif()

    # Create a small CMake script file to execute at build time
    set(_asset_script "${CMAKE_BINARY_DIR}/plaster_assets_copy_${PAA_TARGET}.cmake")
    file(WRITE "${_asset_script}" "${copy_script}")

    # Attach post-build step to target
    add_custom_command(TARGET ${PAA_TARGET}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -P "${_asset_script}"
        BYPRODUCTS "${PAA_OUTPUT_DIR}"
        COMMENT "[assets] Copying assets for target '${PAA_TARGET}' -> ${PAA_OUTPUT_DIR}"
        VERBATIM
    )

    # Expose a convenience property for tooling/IDE integrations
    set_property(TARGET ${PAA_TARGET} PROPERTY PLASTER_ASSETS_DIR "${PAA_OUTPUT_DIR}")

endfunction()
