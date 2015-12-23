#pragma once

#include "../scene/GameComponent.h"

class TestComponent : public GameComponent {
    public:
        TestComponent(float mspeed) : speed(mspeed) {}
        void SetParent(GameObject* parent);
        void Update();
        void Render(const glm::mat4 &VP);
    private:
        float speed;
        glm::mat4 modelspace;
};
