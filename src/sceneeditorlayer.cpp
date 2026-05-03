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
}

void SceneEditorLayer::OnImGuiRender()
{
    DrawHierarchyPanel();
    DrawInspectorPanel();
    DrawSettingsPanel();
}

void SceneEditorLayer::DrawHierarchyPanel()
{
    ImGui::SetNextWindowPos(ImVec2(0, 20), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(200, ImGui::GetIO().DisplaySize.y - 20), ImGuiCond_Always);
    ImGui::Begin("Hierarchy", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

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
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 300, 20), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(300, (ImGui::GetIO().DisplaySize.y - 20) * 0.6f), ImGuiCond_Always);
    ImGui::Begin("Inspector", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

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

void SceneEditorLayer::DrawSettingsPanel()
{
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 300, 20 + (ImGui::GetIO().DisplaySize.y - 20) * 0.6f), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(300, (ImGui::GetIO().DisplaySize.y - 20) * 0.4f), ImGuiCond_Always);
    ImGui::Begin("Scene Settings", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

    ImGui::Text("Scene summary");
    ImGui::Separator();
    ImGui::Text("Entity count: %d", m_Scene->GetEntityCount());

    Entity* selected = m_Scene->GetSelectedEntity();
    if (selected) {
        ImGui::Text("Selected: %s", selected->GetName().c_str());
    } else {
        ImGui::TextDisabled("No entity selected.");
    }

    ImGui::Separator();
    ImGui::Text("Navigation controls");
    ImGui::BulletText("Right click + drag: orbit camera");
    ImGui::BulletText("W/A/S/D: move target");
    ImGui::BulletText("Q/E: down/up");
    ImGui::BulletText("Z/X: zoom in/out");
    ImGui::BulletText("Left click in viewport: cycle entity selection");

    ImGui::Separator();
    ImGui::Text("Editor tips");
    ImGui::TextWrapped("Use the hierarchy panel to select entities, then adjust position, rotation, scale and color in the inspector.");

    ImGui::End();
}
