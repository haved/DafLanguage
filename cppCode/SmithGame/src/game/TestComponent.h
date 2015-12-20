#pragma once

#include "GameComponent.h"

class TestComponent : public GameComponent {
    public:
        TestComponent(float speed) {
            this->speed = speed;
        }
        void Update();
        void Render(glm::mat4 &VP);
    private:
        float speed;
        float rot=0;
        glm::mat4 modelspace;
};
