#include "imageviewer.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

ImageViewer::ImageViewer() : width(0), height(0), texture(0), window(nullptr)
{}

ImageViewer::~ImageViewer()
{
    if (texture) {
        glDeleteTextures(1, &texture);
    }
}

bool ImageViewer::Load(const std::vector<Color>& pixels, int h)
{
    if (pixels.size() % h != 0) {
        return false;
    }

    height = h;
    width = pixels.size() / h;
    this->pixels = pixels;
    return true;
}

void ImageViewer::CreateTexture()
{
    if (texture) {
        glDeleteTextures(1, &texture);
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
                 GL_RGBA, GL_FLOAT, pixels.data());
}

void ImageViewer::Show(const std::string& title)
{
    glfwInit();
    window = glfwCreateWindow(width + 100, height + 100, title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    CreateTexture();
    RenderLoop(title);

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void ImageViewer::RenderLoop(const std::string& title)
{
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        bool open = true;
        ImGui::Begin(title.c_str(), &open, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("Resolution: %dx%d", width, height);
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        ImGui::Image((void*)(intptr_t)texture, ImVec2((float)width, (float)height));
        if (!open)
            glfwSetWindowShouldClose(window, true);
        ImGui::End();

        ImGui::Render();
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }
}
