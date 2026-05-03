#ifndef RENDERLAYER_H
#define RENDERLAYER_H

#include "layer.h"

class RendererLayer : public Layer
{
public:
    RendererLayer();
    virtual ~RendererLayer() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate() override;
    virtual void OnImGuiRender() override;

private:
    void ResizeFramebuffer(int width, int height);

private:
    unsigned int m_Framebuffer = 0;
    unsigned int m_Texture = 0;
    unsigned int m_RBO = 0;

    int m_Width = 1280;
    int m_Height = 720;
};

#endif // RENDERLAYER_H
