#ifndef SCENEEDITORLAYER_H
#define SCENEEDITORLAYER_H

#include "layer.h"

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
    void DrawSettingsPanel();

private:
    Scene* m_Scene;
};

#endif // SCENEEDITORLAYER_H
