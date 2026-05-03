#include "scene.h"
#include <algorithm>

Scene::Scene() = default;

Entity& Scene::CreateEntity(const std::string& name)
{
    m_Entities.emplace_back(std::make_unique<Entity>(name));
    int newIndex = static_cast<int>(m_Entities.size()) - 1;
    SetSelectedEntity(newIndex);
    return *m_Entities.back();
}

void Scene::DeleteSelectedEntity()
{
    if (m_SelectedIndex < 0 || m_SelectedIndex >= static_cast<int>(m_Entities.size()))
        return;

    m_Entities.erase(m_Entities.begin() + m_SelectedIndex);
    if (m_Entities.empty()) {
        m_SelectedIndex = -1;
        return;
    }

    m_SelectedIndex = std::clamp(m_SelectedIndex, 0, static_cast<int>(m_Entities.size()) - 1);
}

Entity* Scene::GetSelectedEntity()
{
    if (m_SelectedIndex < 0 || m_SelectedIndex >= static_cast<int>(m_Entities.size()))
        return nullptr;
    return m_Entities[m_SelectedIndex].get();
}

const Entity* Scene::GetSelectedEntity() const
{
    if (m_SelectedIndex < 0 || m_SelectedIndex >= static_cast<int>(m_Entities.size()))
        return nullptr;
    return m_Entities[m_SelectedIndex].get();
}

void Scene::SetSelectedEntity(int index)
{
    if (index < 0 || index >= static_cast<int>(m_Entities.size())) {
        m_SelectedIndex = -1;
        return;
    }

    if (m_SelectedIndex >= 0 && m_SelectedIndex < static_cast<int>(m_Entities.size())) {
        m_Entities[m_SelectedIndex]->SetSelected(false);
    }

    m_SelectedIndex = index;
    m_Entities[m_SelectedIndex]->SetSelected(true);
}

int Scene::GetSelectedEntityIndex() const
{
    return m_SelectedIndex;
}

std::vector<Entity*> Scene::GetEntities()
{
    std::vector<Entity*> list;
    list.reserve(m_Entities.size());
    for (auto& entity : m_Entities)
        list.push_back(entity.get());
    return list;
}

int Scene::GetEntityCount() const
{
    return static_cast<int>(m_Entities.size());
}
