#ifndef SCENEEDITORLAYER_H
#define SCENEEDITORLAYER_H

#include "layer.h"
#include <string>

class Scene;

class SceneEditorLayer : public Layer
{
public:
    SceneEditorLayer(Scene* scene);
    virtual ~SceneEditorLayer() = default;

    virtual void OnAttach() override;
    virtual void OnImGuiRender() override;

private:
    void DrawHierarchyPanel();
    void DrawInspectorPanel();

private:
    Scene* m_Scene;
    std::string m_NameBuffer;
};

#endif // SCENEEDITORLAYER_H
