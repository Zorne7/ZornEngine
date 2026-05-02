#ifndef APPLICATION_H
#define APPLICATION_H

#include "window.h"

class Application
{
public:
    Application();
    ~Application();

    void Run();

private:
    void Init();
    void Shutdown();

private:
    Window* m_Window;
    bool m_Running = true;
};

#endif // APPLICATION_H
