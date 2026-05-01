cmake_minimum_required (VERSION 3.10)

set(PRJ_NAME ZornEngine)

project("${PRJ_NAME}")

add_subdirectory(ext/glfw)

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
target_link_libraries(${PRJ_NAME} PRIVATE glfw)

target_include_directories(${PRJ_NAME} PRIVATE src)
target_include_directories(${PRJ_NAME} PRIVATE ext/imgui ext/imgui/backends)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PRJ_NAME} PROPERTY CXX_STANDARD 20)
endif()
