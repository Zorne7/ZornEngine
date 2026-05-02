# ZornEngine

A modern graphics engine built with C++ and OpenGL, designed for rendering and GUI applications with immediate-mode UI capabilities.

## Overview

ZornEngine is a C++ graphics engine that provides a foundation for building real-time graphics applications. It combines powerful graphics rendering with an intuitive immediate-mode UI system, making it ideal for game development, visualization tools, and graphics applications.

## Key Features

- **Real-time 3D Graphics**: Hardware-accelerated rendering using OpenGL
- **Immediate-Mode GUI**: Built-in ImGui integration for quick UI development
- **Cross-platform Window Management**: Native window handling via GLFW
- **Event System**: Integrated input and window event handling
- **Layer-based Architecture**: Modular design with application and GUI layers

## Dependencies

ZornEngine relies on the following external libraries located in the `ext/` directory:

### [GLFW](ext/glfw/)
Modern OpenGL context and window management library. Handles:
- Window creation and lifecycle management
- Input events (keyboard, mouse)
- Monitor and display configuration
- Cross-platform compatibility

### [ImGui](ext/imgui/)
Immediate-mode graphical user interface library. Provides:
- Immediate-mode UI rendering
- Interactive UI controls and widgets
- Flexible styling and theming
- Minimal coupling with application logic

### [GLAD](ext/glad/)
OpenGL loader library. Responsible for:
- Loading OpenGL function pointers
- Managing OpenGL extensions
- Version compatibility

## Requirements
- C++17 or later
- CMake 3.16+
- MinGW (or compatible C++ compiler)
- OpenGL 3.3+

## License

See individual dependency licenses in their respective directories.
