#pragma once
#include "GameObject.h"
#include <memory>

#include <glm/common.hpp>

class Scene {
    public:
        Scene();
        void AddObject(std::shared_ptr<GameObject> object);
        void Update();
        void Render(const glm::mat4 &VP);
    private:
        GameObject root;
};
