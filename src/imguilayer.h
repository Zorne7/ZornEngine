#ifndef IMGUILAYER_H
#define IMGUILAYER_H

#include "layer.h"

class Window;

class ImGuiLayer : public Layer
{
public:
    ImGuiLayer(Window* window);
    ~ImGuiLayer();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnImGuiRender() override;

    virtual void Begin() override;
    virtual void End() override;

private:
    Window* m_Window;
};


#endif // IMGUILAYER_H
