#pragma once

#include "../scene/GameComponent.h"
#include "../rendering/Mesh.h"
#include <memory>

class TestComponent : public GameComponent {
    public:
        TestComponent(float speed, std::shared_ptr<Mesh> mesh) : m_speed(speed), m_mesh(mesh) {}
        void SetParent(GameObject* parent);
        void Update();
        void Render(const glm::mat4 &VP);
    private:
        float m_speed;
        std::shared_ptr<Mesh> m_mesh;
};
