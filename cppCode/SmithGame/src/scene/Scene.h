#pragma once
#include "GameObject.h"
#include <memory>

#include <glm/common.hpp>

class Scene {
    public:
        void AddObject(GameObject& object);
        void Update();
        void Render(glm::mat4 &VP);
    private:
        GameObject root;
};
