#include "renderlayer.h"
#include "imgui.h"
#include <glad/glad.h>

RendererLayer::RendererLayer()
    : Layer("RendererLayer")
{
}

void RendererLayer::OnAttach()
{
    glEnable(GL_DEPTH_TEST);

    glGenFramebuffers(1, &m_Framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);

    // Texture color attachment
    glGenTextures(1, &m_Texture);
    glBindTexture(GL_TEXTURE_2D, m_Texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture, 0);

    // Renderbuffer (depth + stencil)
    glGenRenderbuffers(1, &m_RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RendererLayer::OnDetach()
{
    if (m_RBO) {
        glDeleteRenderbuffers(1, &m_RBO);
        m_RBO = 0;
    }

    if (m_Texture) {
        glDeleteTextures(1, &m_Texture);
        m_Texture = 0;
    }

    if (m_Framebuffer) {
        glDeleteFramebuffers(1, &m_Framebuffer);
        m_Framebuffer = 0;
    }
}

void RendererLayer::ResizeFramebuffer(int width, int height)
{
    if (width <= 0 || height <= 0){
        return;
    }

    m_Width = width;
    m_Height = height;

    glBindTexture(GL_TEXTURE_2D, m_Texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);
}

void RendererLayer::OnUpdate()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
    glViewport(0, 0, m_Width, m_Height);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // TODO: draw your scene here

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RendererLayer::OnImGuiRender()
{
    ImGui::Begin("Viewport");

    ImVec2 size = ImGui::GetContentRegionAvail();
    if ((int)size.x != m_Width || (int)size.y != m_Height){
        ResizeFramebuffer((int)size.x, (int)size.y);
    }

    ImGui::Image((void*)(intptr_t)m_Texture, size, ImVec2(0, 1), ImVec2(1, 0));

    ImGui::End();
}
