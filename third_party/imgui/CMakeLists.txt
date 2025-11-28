cmake_minimum_required(VERSION 3.15)
project(imgui)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Core ImGui sources
set(IMGUI_SOURCES
    imgui.cpp
    imgui_demo.cpp
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    backends/imgui_impl_sdl3.cpp
    backends/imgui_impl_sdlrenderer3.cpp  # 确保这个文件被包含
)

set(IMGUI_HEADERS
    imgui.h
    imgui_internal.h
    imconfig.h
    imstb_rectpack.h
    imstb_textedit.h
    imstb_truetype.h
)

# Backend sources for GLFW + OpenGL3
set(IMGUI_BACKEND_SOURCES
    backends/imgui_impl_sdl3.cpp
    backends/imgui_impl_opengl3.cpp
)

set(IMGUI_BACKEND_HEADERS
    backends/imgui_impl_sdl3.h
    backends/imgui_impl_opengl3.h
)

# Create imgui library
add_library(imgui STATIC
    ${IMGUI_SOURCES}
    ${IMGUI_HEADERS}
    ${IMGUI_BACKEND_SOURCES}
    ${IMGUI_BACKEND_HEADERS}
)

# Include directories
target_include_directories(imgui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/backends
)

# Link with GLFW
target_link_libraries(imgui PUBLIC SDL3::SDL3)

# Platform-specific configurations
if(WIN32)
    target_link_libraries(imgui PUBLIC opengl32)
elseif(APPLE)
    find_package(OpenGL REQUIRED)
    target_link_libraries(imgui PUBLIC OpenGL::GL)
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(imgui PUBLIC OpenGL::GL)
endif()

# Compiler-specific settings
if(MSVC)
    target_compile_definitions(imgui PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

# Export the library
add_library(imgui::imgui ALIAS imgui)
