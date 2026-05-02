#ifndef LAYER_H
#define LAYER_H

#include <string>

class Layer
{
public:
    Layer(const std::string& name = "Layer") : m_Name(name) {}
    virtual ~Layer() = default;

    virtual void OnAttach() {}
    virtual void OnDetach() {}
    virtual void OnUpdate() {}
    virtual void OnImGuiRender() {}

    virtual void Begin() {}
    virtual void End() {}

    const std::string& GetName() const { return m_Name; }

protected:
    std::string m_Name;
};

#endif // LAYER_H
