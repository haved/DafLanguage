#include "TestComponent.h"
#include "../Time.h"
#define GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>
#include "GameObject.h"

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
    glColor3f(modf(GetCurrentMillis()/1000.f, &tmp), modf(GetCurrentMillis()/2000.f, &tmp), modf(GetCurrentMillis()/3000.f, &tmp));
    glVertex3f(-1, -1, -1);
    glVertex3f( 1, -1, -1);
    glVertex3f( 1, -1,  1);
    glVertex3f(-1, -1,  1);
    glColor3f(modf(GetCurrentMillis()/2000.f, &tmp), modf(GetCurrentMillis()/3000.f, &tmp), modf(GetCurrentMillis()/1000.f, &tmp));
    glVertex3f( 1, -1, -1);
    glVertex3f( 1,  1, -1);
    glVertex3f( 1,  1,  1);
    glVertex3f( 1, -1,  1);
    glColor3f(modf(GetCurrentMillis()/3000.f, &tmp), modf(GetCurrentMillis()/1000.f, &tmp), modf(GetCurrentMillis()/2000.f, &tmp));
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, -1,  1);
    glVertex3f(-1,  1,  1);
    glVertex3f(-1,  1, -1);
    glColor3f(modf(GetCurrentMillis()/2000.f, &tmp), modf(GetCurrentMillis()/1000.f, &tmp), modf(GetCurrentMillis()/3000.f, &tmp));
    glVertex3f(-1,  1, -1);
    glVertex3f(-1,  1,  1);
    glVertex3f( 1,  1,  1);
    glVertex3f( 1,  1, -1);
    glEnd();
    glPopMatrix();
}
