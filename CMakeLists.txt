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
    "ext/imgui/*.h"
    "ext/imgui/*.c"
    "ext/imgui/*.cpp"
    "ext/imgui/backends/*.h"
    "ext/imgui/backends/*.c"
    "ext/imgui/backends/*.cpp"
)

file(GLOB_RECURSE PRJ_SRC
    "src/*.h"
    "src/*.c"
    "src/*.cpp"
)

add_executable(${PRJ_NAME}
    # Headers
    "src/imageviewer.h"

    # Sources
    "src/main.cpp"    
    "src/imageviewer.cpp"

    ${GLFW_SRC}

    ${IMGUI_SRC}
)

find_package(OpenGL REQUIRED)

target_link_libraries(${PRJ_NAME} PRIVATE OpenGL::GL glu32 dwmapi)

target_include_directories(${PRJ_NAME} PRIVATE src)
target_include_directories(${PRJ_NAME} PRIVATE ext/glfw/src ext/glfw/include/GLFW)
target_include_directories(${PRJ_NAME} PRIVATE ext/imgui ext/imgui/backends)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PRJ_NAME} PROPERTY CXX_STANDARD 20)
endif()
