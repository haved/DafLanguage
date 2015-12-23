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

void TestComponent::Render(const glm::mat4 &MVP) {
    glPushMatrix();
    glLoadMatrixf(&MVP[0][0]);
    m_mesh->Draw();
    glPopMatrix();
}
