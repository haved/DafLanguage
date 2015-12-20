#pragma once

#include <vector>
#include <memory>
#include "GameComponent.h"
#include <glm/common.hpp>

class Scene;

class GameObject {
public:
    GameObject();
    void SetScene(Scene* scene);
    void SetParent(GameObject* object);
    void AddChild(GameObject &child);
    void AddComponent(std::shared_ptr<GameComponent> component);
    void Update();
    void Render(glm::mat4 &VP);
private:
    std::vector<GameObject> children;
    std::vector<std::shared_ptr<GameComponent>> components;
    GameObject* parent;
    Scene* scene;
};
