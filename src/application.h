#ifndef APPLICATION_H
#define APPLICATION_H

#include "window.h"
#include "layer.h"
#include <vector>

class ImGuiLayer;

class Application
{
public:
    Application();
    ~Application();

    void Run();
    void PushLayer(Layer* layer);

private:
    Window* m_Window;
    bool m_Running = true;

    ImGuiLayer *m_imGuiLayer;
    std::vector<Layer*> m_Layers;
};

#endif // APPLICATION_H
