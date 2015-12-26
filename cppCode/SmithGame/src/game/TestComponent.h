#pragma once

#include "../scene/GameComponent.h"
#include "../rendering/MeshRaw.h"
#include <memory>
#include "../rendering/shaders/BasicShader.h"

class TestComponent : public GameComponent {
    public:
        TestComponent(float speed, std::shared_ptr<MeshRaw> mesh, std::shared_ptr<BasicShader> shader) : m_speed(speed), m_mesh(mesh), m_shader(shader) {}
        void SetParent(GameObject* parent);
        void Update();
        void Render(const glm::mat4 &VP);
    private:
        float m_speed;
        std::shared_ptr<MeshRaw> m_mesh;
        std::shared_ptr<BasicShader> m_shader;
};
