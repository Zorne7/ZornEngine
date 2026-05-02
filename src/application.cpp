#include "application.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

Application::Application()
{
    Init();
}

Application::~Application()
{
    Shutdown();
}

void Application::Init()
{
    m_Window = new Window(1280, 720, "ZornEngine");

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(m_Window->GetNativeWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void Application::Shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    delete m_Window;
}

void Application::Run()
{
    while (!m_Window->ShouldClose()) {
        m_Window->PollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // --- UI ---
        ImGui::Begin("ZornEngine");
        ImGui::Text("Engine running!");
        ImGui::End();
        // -----------

        ImGui::Render();
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        m_Window->SwapBuffers();
    }
}