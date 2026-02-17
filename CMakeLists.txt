cmake_minimum_required(VERSION 3.16)
project(Chess VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Collect all source files recursively
file(GLOB_RECURSE SOURCES
    "main.cpp"
    "src/*.cpp"
)

# Create executable
add_executable(Chess ${SOURCES})

# Include paths so headers can be found
target_include_directories(Chess PRIVATE
    src
    src/core
    src/graphics
    src/input
    src/audio
    src/vendor
    src/game
    src/game/pieces
    src/game/logic
    src/game/gameplay
)

# ── OpenGL ────────────────────────────────────────────────────────────────────
find_package(OpenGL REQUIRED)

# ── GLEW ─────────────────────────────────────────────────────────────────────
find_package(GLEW REQUIRED)

# ── GLFW ─────────────────────────────────────────────────────────────────────
find_package(glfw3 REQUIRED)

# ── GLM ──────────────────────────────────────────────────────────────────────
find_package(glm REQUIRED)

# ── SDL2 & SDL2_mixer ────────────────────────────────────────────────────────
find_package(SDL2 REQUIRED)

# SDL2_mixer has no official CMake module; use pkg-config as fallback
find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
    pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)
    target_include_directories(Chess PRIVATE ${SDL2_MIXER_INCLUDE_DIRS})
    target_link_libraries(Chess PRIVATE ${SDL2_MIXER_LIBRARIES})
else()
    # Direct fallback for MSYS2/MinGW without pkg-config
    find_library(SDL2_MIXER_LIB NAMES SDL2_mixer REQUIRED)
    target_link_libraries(Chess PRIVATE ${SDL2_MIXER_LIB})
endif()

# ── Link all libraries ────────────────────────────────────────────────────────
target_link_libraries(Chess PRIVATE
    OpenGL::GL
    GLEW::GLEW
    glfw
    SDL2::SDL2
    glm::glm
)

# ── Copy assets to build directory ───────────────────────────────────────────
add_custom_command(TARGET Chess POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:Chess>/assets"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/shaders"
        "$<TARGET_FILE_DIR:Chess>/shaders"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/fonts"
        "$<TARGET_FILE_DIR:Chess>/fonts"
    COMMENT "Copying assets, shaders, and fonts to build directory"
)
