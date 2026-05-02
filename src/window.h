#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
    Window(int width, int height, const std::string& title);
    ~Window();

    void PollEvents();
    void SwapBuffers();
    bool ShouldClose() const;

    GLFWwindow* GetNativeWindow() const { return m_Window; }

private:
    void Init(int width, int height, const std::string& title);
    void Shutdown();

private:
    GLFWwindow* m_Window;
    int m_Width, m_Height;
    std::string m_Title;
};

#endif // WINDOW_H
