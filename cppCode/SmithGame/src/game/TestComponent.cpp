#include "TestComponent.h"
#include "../Time.h"
#define GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>

void TestComponent::Update() {
    rot+=GetDeltaTime()*speed;
}

void TestComponent::Render(glm::mat4 &VP) {
    modelspace = glm::rotate(rot, glm::vec3(0,0,1));
    glm::mat4 MVP = VP*modelspace;
    glPushMatrix();
    glLoadMatrixf(&MVP[0][0]);
    double tmp;
    glColor3f(modf(GetCurrentMillis()/1000.f, &tmp), modf(GetCurrentMillis()/2000.f, &tmp), modf(GetCurrentMillis()/3000.f, &tmp));
    glBegin(GL_QUADS);
    glVertex2f(-1.f,  -1.f);
    glVertex2f( .5f,  -.5f);
    glVertex2f( .5f,   .5f);
    glVertex2f(-.5f,   .5f);
    glEnd();
    glPopMatrix();
}
