cmake_minimum_required (VERSION 3.10)

set(PRJ_NAME ZornEngine)

project("${PRJ_NAME}")

file(GLOB_RECURSE GLFW_SRC
    "ext/glfw/include/GLFW/*.h"
    "ext/glfw/src/*.h"
    "ext/glfw/src/*.c"
    "ext/glfw/src/*.cpp"
)

file(GLOB_RECURSE IMGUI_SRC
    # Core
    "ext/imgui/imgui.cpp"
    "ext/imgui/imgui_draw.cpp"
    "ext/imgui/imgui_tables.cpp"
    "ext/imgui/imgui_widgets.cpp"
    "ext/imgui/imgui_demo.cpp"
    # Backend
    "ext/imgui/backends/imgui_impl_glfw.cpp"
    "ext/imgui/backends/imgui_impl_opengl3.cpp"
)

file(GLOB_RECURSE PRJ_SRC
    "src/*.h"
    "src/*.c"
    "src/*.cpp"
)

add_executable(${PRJ_NAME}

    ${PRJ_SRC}

    ${GLFW_SRC}

    ${IMGUI_SRC}
)

find_package(OpenGL REQUIRED)

target_link_libraries(${PRJ_NAME} PRIVATE OpenGL::GL glu32 dwmapi)

target_include_directories(${PRJ_NAME} PRIVATE src)
target_include_directories(${PRJ_NAME} PRIVATE ext/glfw/src ext/glfw/include)
target_include_directories(${PRJ_NAME} PRIVATE ext/imgui ext/imgui/backends)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PRJ_NAME} PROPERTY CXX_STANDARD 20)
endif()
