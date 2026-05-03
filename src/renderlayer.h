#ifndef RENDERLAYER_H
#define RENDERLAYER_H

#include "layer.h"
#include "math.h"

class Scene;
class Shader;
class Window;

class RendererLayer : public Layer
{
public:
    RendererLayer(Scene* scene, Window* window);
    virtual ~RendererLayer() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate() override;
    virtual void OnImGuiRender() override;

private:
    void ResizeFramebuffer(int width, int height);
    void SetupRenderResources();
    void DestroyRenderResources();
    void RenderScene();
    void UpdateEditorCamera();

private:
    Scene* m_Scene;
    Window* m_Window;
    Shader* m_Shader = nullptr;
    unsigned int m_VAO = 0;
    unsigned int m_VBO = 0;

    unsigned int m_Framebuffer = 0;
    unsigned int m_Texture = 0;
    unsigned int m_RBO = 0;

    int m_Width = 1280;
    int m_Height = 720;

    Math::Vec3 m_CameraTarget = Math::Vec3(0.0f, 0.0f, 0.0f);
    Math::Vec3 m_CameraPosition = Math::Vec3(3.0f, 3.0f, 3.0f);
    Math::Vec3 m_CameraUp = Math::Vec3(0.0f, 1.0f, 0.0f);
    float m_CameraYaw = -135.0f;
    float m_CameraPitch = -35.0f;
    float m_CameraDistance = 8.0f;
    double m_LastMouseX = 0.0;
    double m_LastMouseY = 0.0;
    bool m_FirstMouse = true;
    bool m_ViewportHovered = false;
    float m_LastFrameTime = 0.0f;
};

#endif // RENDERLAYER_H
