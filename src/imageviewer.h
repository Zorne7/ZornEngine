#pragma once

#include <string>
#include <vector>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

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
    void CreateWindowAndContext(const std::string &title);
    void DestroyWindowAndContext();
    void RenderLoop(const std::string &title);

    int height, width;
    std::vector<Color> pixels;
    GLuint texture;

    // Win32
    HWND hwnd;
    HDC hdc;
    HGLRC glrc;
};
