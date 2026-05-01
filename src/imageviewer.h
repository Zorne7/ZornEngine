#pragma once

#include <string>
#include <vector>
#include <windows.h>
#include <GLFW/glfw3.h>

struct Color
{
    float r;
    float g;
    float b;
    float a;
};

class ImageViewer
{
public:
    ImageViewer();
    ~ImageViewer();

    bool Load(const std::vector<Color> &pixels, int h);
    void Show(const std::string &title = "Image Viewer");

private:
    void CreateTexture();
    void RenderLoop(const std::string &title);

    int height, width;
    std::vector<Color> pixels;
    GLuint texture;

    GLFWwindow* window;
};
