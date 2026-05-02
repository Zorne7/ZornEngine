#ifndef APPLICATION_H
#define APPLICATION_H

#include "window.h"
#include "layer.h"
#include <vector>

class Application
{
public:
    Application();
    ~Application();

    void Run();
    void PushLayer(Layer* layer);

private:
    void Init();
    void Shutdown();

private:
    Window* m_Window;
    bool m_Running = true;

    std::vector<Layer*> m_Layers;
};
#endif // APPLICATION_H
