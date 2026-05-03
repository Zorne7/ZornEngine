#include "sceneeditorlayer.h"
#include "scene.h"
#include "entity.h"
#include "imgui.h"
#include <cstring>

SceneEditorLayer::SceneEditorLayer(Scene* scene)
    : Layer("SceneEditorLayer"), m_Scene(scene)
{
}

void SceneEditorLayer::OnAttach()
{
    m_NameBuffer.reserve(128);
}

void SceneEditorLayer::OnImGuiRender()
{
    DrawHierarchyPanel();
    DrawInspectorPanel();
}

void SceneEditorLayer::DrawHierarchyPanel()
{
    ImGui::Begin("Hierarchy");

    if (ImGui::Button("Create Entity")) {
        Entity& entity = m_Scene->CreateEntity("New Entity");
        entity.GetTransform().Position = Math::Vec3(0.0f, 0.0f, 0.0f);
    }

    ImGui::Separator();

    auto entities = m_Scene->GetEntities();
    for (int index = 0; index < static_cast<int>(entities.size()); ++index) {
        Entity* entity = entities[index];
        bool isSelected = entity->IsSelected();

        if (ImGui::Selectable(entity->GetName().c_str(), isSelected)) {
            m_Scene->SetSelectedEntity(index);
        }
    }

    ImGui::End();
}

void SceneEditorLayer::DrawInspectorPanel()
{
    ImGui::Begin("Inspector");

    Entity* entity = m_Scene->GetSelectedEntity();
    if (!entity) {
        ImGui::TextDisabled("No entity selected.");
        ImGui::End();
        return;
    }

    char nameBuffer[128];
    strncpy(nameBuffer, entity->GetName().c_str(), sizeof(nameBuffer) - 1);
    nameBuffer[sizeof(nameBuffer) - 1] = '\0';

    if (ImGui::InputText("Name", nameBuffer, sizeof(nameBuffer))) {
        entity->SetName(std::string(nameBuffer));
    }

    TransformComponent& transform = entity->GetTransform();
    ImGui::DragFloat3("Position", &transform.Position.x, 0.1f);
    ImGui::DragFloat3("Rotation", &transform.Rotation.x, 1.0f);
    ImGui::DragFloat3("Scale", &transform.Scale.x, 0.1f, 0.01f, 10.0f);

    RenderComponent& render = entity->GetRenderComponent();
    ImGui::ColorEdit3("Color", &render.Color.x);

    ImGui::Separator();

    if (ImGui::Button("Delete Entity")) {
        m_Scene->DeleteSelectedEntity();
    }

    ImGui::End();
}
