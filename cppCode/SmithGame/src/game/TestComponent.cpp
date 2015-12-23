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
    this->parent->GetMutRotPointer()->z+=GetDeltaTime()*speed;
}

void TestComponent::Render(const glm::mat4 &MVP) {
    glPushMatrix();
    glLoadMatrixf(&MVP[0][0]);
    double tmp;
    glBegin(GL_QUADS);
    glColor3f(modf(GetCurrentMillis()/1111.f, &tmp), modf(GetCurrentMillis()/2099.f, &tmp), modf(GetCurrentMillis()/3667.f, &tmp));
    glVertex3f(-1, -1, -1);
    glVertex3f( 1, -1, -1);
    glVertex3f( 1, -1,  1);
    glVertex3f(-1, -1,  1);
    glColor3f(modf(GetCurrentMillis()/2350.f, &tmp), modf(GetCurrentMillis()/3861.f, &tmp), modf(GetCurrentMillis()/1145.f, &tmp));
    glVertex3f( 1, -1, -1);
    glVertex3f( 1,  1, -1);
    glVertex3f( 1,  1,  1);
    glVertex3f( 1, -1,  1);
    glColor3f(modf(GetCurrentMillis()/3100.f, &tmp), modf(GetCurrentMillis()/1560.f, &tmp), modf(GetCurrentMillis()/2050.f, &tmp));
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, -1,  1);
    glVertex3f(-1,  1,  1);
    glVertex3f(-1,  1, -1);
    glColor3f(modf(GetCurrentMillis()/2500.f, &tmp), modf(GetCurrentMillis()/1750.f, &tmp), modf(GetCurrentMillis()/3111.f, &tmp));
    glVertex3f(-1,  1, -1);
    glVertex3f(-1,  1,  1);
    glVertex3f( 1,  1,  1);
    glVertex3f( 1,  1, -1);
    glEnd();
    glPopMatrix();
}
