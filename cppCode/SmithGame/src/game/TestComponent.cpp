#include "TestComponent.h"
#include "../Time.h"
#define GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>
#include "../scene/GameObject.h"

void TestComponent::SetParent(GameObject* parent) {
    this->parent = parent;
    if(parent!=NULL)
        parent->SetToRenderSelf();
}

void TestComponent::Update() {
    this->parent->GetMutRotPointer()->z+=GetDeltaTime()*m_speed;
}

glm::vec4 white(1,1,1,1);
void TestComponent::Render(const glm::mat4 &MVP) {
    m_shader->Bind();
    m_shader->SetMVP(MVP);
    m_shader->SetModelspaceMatrix(parent->GetGlobalModelspace());
    m_shader->SetColor(white);
    m_mesh->Draw();
}
