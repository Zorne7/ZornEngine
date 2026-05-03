#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "math.h"

struct TransformComponent {
    Math::Vec3 Position{0.0f, 0.0f, 0.0f};
    Math::Vec3 Rotation{0.0f, 0.0f, 0.0f};
    Math::Vec3 Scale{1.0f, 1.0f, 1.0f};
};

struct RenderComponent {
    Math::Vec3 Color{0.8f, 0.6f, 0.2f};
};

class Entity {
public:
    Entity(const std::string& name = "Entity")
        : m_Name(name)
    {
    }

    const std::string& GetName() const { return m_Name; }
    void SetName(const std::string& name) { m_Name = name; }

    TransformComponent& GetTransform() { return m_Transform; }
    const TransformComponent& GetTransform() const { return m_Transform; }

    RenderComponent& GetRenderComponent() { return m_RenderComponent; }
    const RenderComponent& GetRenderComponent() const { return m_RenderComponent; }

    bool IsSelected() const { return m_Selected; }
    void SetSelected(bool selected) { m_Selected = selected; }

private:
    std::string m_Name;
    TransformComponent m_Transform;
    RenderComponent m_RenderComponent;
    bool m_Selected = false;
};

#endif // ENTITY_H
