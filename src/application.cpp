#include "application.h"
#include "imguilayer.h"

Application::Application()
{
    Init();
    PushLayer(new ImGuiLayer(m_Window));
}

Application::~Application()
{
    Shutdown();
}

void Application::Init()
{
    m_Window = new Window(1280, 720, "ZornEngine");
}

void Application::Shutdown()
{
    delete m_Window;
}

void Application::PushLayer(Layer* layer)
{
    m_Layers.push_back(layer);
    layer->OnAttach();
}

void Application::Run()
{
    while (!m_Window->ShouldClose()) {
        m_Window->PollEvents();

        for (Layer* layer : m_Layers) {
            layer->OnUpdate();
            layer->Begin();
        }

        for (Layer* layer : m_Layers){
            layer->OnImGuiRender();
            layer->End();
        }

        m_Window->SwapBuffers();
    }
}
