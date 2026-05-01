cmake_minimum_required(VERSION 3.10)

set(PRJ_NAME ZornEngine)
project(${PRJ_NAME})

# ------------ External libraries ------------

# GLFW
add_subdirectory(ext/glfw)

# ImGui
set(IMGUI_SRC
    ext/imgui/imgui.cpp
    ext/imgui/imgui_draw.cpp
    ext/imgui/imgui_tables.cpp
    ext/imgui/imgui_widgets.cpp
    ext/imgui/imgui_demo.cpp

    ext/imgui/backends/imgui_impl_glfw.cpp
    ext/imgui/backends/imgui_impl_opengl3.cpp
)

add_library(imgui ${IMGUI_SRC})
target_include_directories(imgui PUBLIC
    ext/imgui
    ext/imgui/backends
    ext/glfw/include
)

# ------------ Project Sources ------------

file(GLOB_RECURSE PRJ_SRC
    "src/*.cpp"
    "src/*.h"
)

add_executable(${PRJ_NAME} ${PRJ_SRC})

set_property(TARGET ${PRJ_NAME} PROPERTY CXX_STANDARD 20)

# ------------ Linked Libraries ------------

find_package(OpenGL REQUIRED)

target_link_libraries(${PRJ_NAME}
    PRIVATE
        glfw
        imgui
        OpenGL::GL
)
