#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <string>
#include <vector>

#include "entity.h"

class Scene {
public:
    Scene();
    ~Scene() = default;

    Entity& CreateEntity(const std::string& name = "Entity");
    void DeleteSelectedEntity();

    Entity* GetSelectedEntity();
    const Entity* GetSelectedEntity() const;

    void SetSelectedEntity(int index);
    int GetSelectedEntityIndex() const;

    std::vector<Entity*> GetEntities();
    int GetEntityCount() const;

private:
    std::vector<std::unique_ptr<Entity>> m_Entities;
    int m_SelectedIndex = -1;
};

#endif // SCENE_H
