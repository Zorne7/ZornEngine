#include "renderlayer.h"
#include "scene.h"
#include "shader.h"
#include "math.h"
#include "imgui.h"
#include <glad/glad.h>
#include <iostream>

static const float s_CubeVertices[] = {
    // positions
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f
};

static const std::string s_VertexShaderSource = R"(
#version 330 core
layout(location = 0) in vec3 a_Position;
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;
void main()
{
    gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0);
}
)";

static const std::string s_FragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
uniform vec3 u_Color;
void main()
{
    FragColor = vec4(u_Color, 1.0);
}
)";

RendererLayer::RendererLayer(Scene* scene)
    : Layer("RendererLayer"), m_Scene(scene)
{
}

void RendererLayer::OnAttach()
{
    glEnable(GL_DEPTH_TEST);

    glGenFramebuffers(1, &m_Framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);

    glGenTextures(1, &m_Texture);
    glBindTexture(GL_TEXTURE_2D, m_Texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture, 0);

    glGenRenderbuffers(1, &m_RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Framebuffer incomplete!" << std::endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    SetupRenderResources();
}

void RendererLayer::OnDetach()
{
    DestroyRenderResources();

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

void RendererLayer::SetupRenderResources()
{
    m_Shader = new Shader(s_VertexShaderSource, s_FragmentShaderSource);

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(s_CubeVertices), s_CubeVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);

    glBindVertexArray(0);
}

void RendererLayer::DestroyRenderResources()
{
    if (m_Shader) {
        delete m_Shader;
        m_Shader = nullptr;
    }

    if (m_VBO) {
        glDeleteBuffers(1, &m_VBO);
        m_VBO = 0;
    }

    if (m_VAO) {
        glDeleteVertexArrays(1, &m_VAO);
        m_VAO = 0;
    }
}

void RendererLayer::ResizeFramebuffer(int width, int height)
{
    if (width <= 0 || height <= 0)
        return;

    m_Width = width;
    m_Height = height;

    glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);

    glBindTexture(GL_TEXTURE_2D, m_Texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RendererLayer::OnUpdate()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
    glViewport(0, 0, m_Width, m_Height);

    glClearColor(0.1f, 0.1f, 0.11f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    RenderScene();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RendererLayer::RenderScene()
{
    if (!m_Shader)
        return;

    Math::Mat4 projection = Math::Perspective(Math::ToRadians(45.0f), (float)m_Width / (float)m_Height, 0.1f, 100.0f);
    Math::Mat4 view = Math::LookAt(Math::Vec3(3.0f, 3.0f, 3.0f), Math::Vec3(0.0f, 0.0f, 0.0f), Math::Vec3(0.0f, 1.0f, 0.0f));

    m_Shader->Bind();
    m_Shader->SetMat4("u_View", view);
    m_Shader->SetMat4("u_Projection", projection);

    glBindVertexArray(m_VAO);

    for (Entity* entity : m_Scene->GetEntities()) {
        const TransformComponent& transform = entity->GetTransform();

        Math::Mat4 model = Math::Translate(transform.Position)
            * Math::RotateZ(Math::ToRadians(transform.Rotation.z))
            * Math::RotateY(Math::ToRadians(transform.Rotation.y))
            * Math::RotateX(Math::ToRadians(transform.Rotation.x))
            * Math::Scale(transform.Scale);

        m_Shader->SetMat4("u_Model", model);
        m_Shader->SetFloat3("u_Color", entity->GetRenderComponent().Color);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glBindVertexArray(0);
    m_Shader->Unbind();
}

void RendererLayer::OnImGuiRender()
{
    ImGui::Begin("Viewport");

    ImVec2 size = ImGui::GetContentRegionAvail();
    if ((int)size.x != m_Width || (int)size.y != m_Height) {
        ResizeFramebuffer((int)size.x, (int)size.y);
    }

    ImGui::Image((void*)(intptr_t)m_Texture, size, ImVec2(0, 1), ImVec2(1, 0));

    ImGui::End();
}
