#include "TestComponent.h"
#include "../Time.h"
#define GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>
#include "../scene/GameObject.h"
#include <glm/glm.hpp>
#include "../common.h"

TestComponent::TestComponent(float speed, std::shared_ptr<MeshReference> mesh, std::shared_ptr<TextureReference> texture, std::shared_ptr<BasicShader> shader)
: m_speed(speed), m_mesh(mesh), m_texture(texture), m_shader(shader) {}

void TestComponent::SetParent(GameObject* parent) {
    this->parent = parent;
    if(parent!=NULL)
        parent->SetToRenderSelf();
}

void TestComponent::Update() {
    glm::vec3* mutRot = parent->GetMutRotPointer();
    mutRot->z+=GetDeltaTime()*m_speed;
    mutRot->x+=glm::cos(GetIngameSeconds()/4)/30*m_speed;
    mutRot->y=glm::sin(GetIngameSeconds()/7*m_speed)*TAU;
}

#include <iostream>
glm::vec4 white(1,1,1,1);
void TestComponent::Render(const glm::mat4 &MVP) {
    m_shader->Bind();
    m_shader->SetMVP(MVP);
    m_shader->SetModelspaceMatrix(parent->GetGlobalModelspace());
    m_shader->SetColor(white);
    m_texture->Bind();
    m_mesh->Draw();
}
