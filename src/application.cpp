#include "application.h"
#include "imguilayer.h"
#include "renderlayer.h"

Application::Application()
{
    m_Window = new Window(1280, 720, "ZornEngine");
    m_imGuiLayer = new ImGuiLayer(m_Window);

    PushLayer(new RendererLayer());
    PushLayer(m_imGuiLayer);
}

Application::~Application()
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

        // 1) Update layers
        for (Layer* layer : m_Layers){
            layer->OnUpdate();
        }

        // 2) Start frame
        m_imGuiLayer->Begin();

        // 3) Render layers
        for (Layer* layer : m_Layers){
            layer->OnImGuiRender();
        }

        // 4) End frame
        m_imGuiLayer->End();

        m_Window->SwapBuffers();
    }
}
