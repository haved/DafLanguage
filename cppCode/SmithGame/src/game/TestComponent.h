#pragma once

#include "../scene/GameComponent.h"
#include "../asset/MeshReference.h"
#include "../asset/TextureReference.h"
#include <memory>
#include "../rendering/shaders/BasicShader.h"

class TestComponent : public GameComponent {
    public:
        TestComponent(float speed, std::shared_ptr<MeshReference> mesh, std::shared_ptr<TextureReference> texture, std::shared_ptr<BasicShader> shader);
        void SetParent(GameObject* parent);
        void Update();
        void Render(const glm::mat4 &VP);
    private:
        float m_speed;
        std::shared_ptr<MeshReference> m_mesh;
        std::shared_ptr<TextureReference> m_texture;
        std::shared_ptr<BasicShader> m_shader;
};
