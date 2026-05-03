#include "application.h"
#include "imguilayer.h"
#include "renderlayer.h"
#include "scene.h"
#include "sceneeditorlayer.h"

Application::Application()
{
    m_Window = new Window(1280, 720, "ZornEngine");
    m_Scene = new Scene();
    m_imGuiLayer = new ImGuiLayer(m_Window);

    Entity& cube = m_Scene->CreateEntity("Cube");
    cube.GetTransform().Position = Math::Vec3(0.0f, 0.0f, 0.0f);
    cube.GetTransform().Scale = Math::Vec3(1.0f, 1.0f, 1.0f);

    Entity& floor = m_Scene->CreateEntity("Floor");
    floor.GetTransform().Position = Math::Vec3(0.0f, -1.0f, 0.0f);
    floor.GetTransform().Scale = Math::Vec3(5.0f, 0.1f, 5.0f);
    floor.GetRenderComponent().Color = Math::Vec3(0.4f, 0.4f, 0.4f);

    PushLayer(new RendererLayer(m_Scene, m_Window));
    PushLayer(new SceneEditorLayer(m_Scene));
    PushLayer(m_imGuiLayer);
}

Application::~Application()
{
    for (Layer* layer : m_Layers) {
        delete layer;
    }
    delete m_Scene;
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
