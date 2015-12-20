#include "GameWindow.h"
#include "SmithGame.h"
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "Time.h"
#include <cmath>
#include <glm/common.hpp>
#include <glm/gtx/transform.hpp>

void SmithGame::Init() {
    glClearColor(0.3f, 0.5f, 0.9f, 1);
}

float rot = 0;
void SmithGame::NextFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    rot+=GetDeltaTime()*10;
    glm::mat4 matx = glm::rotate(rot, glm::vec3(0,0,1));
    glLoadMatrixf(&matx[0][0]);
    double basj;
    glColor3f(modf(GetCurrentMillis()/1000.f, &basj), modf(GetCurrentMillis()/2000.f, &basj), modf(GetCurrentMillis()/3000.f, &basj));
    glBegin(GL_QUADS);
    glVertex2f(-1.f,  -1.f);
    glVertex2f( .5f,  -.5f);
    glVertex2f( .5f,   .5f);
    glVertex2f(-.5f,   .5f);
    glEnd();
    glPopMatrix();
}

void SmithGame::OnResize(int width, int height) {
    glViewport(0, 0, width, height);
}

void SmithGame::Destroy() {

}

int main(int argc, char *argv[]) {
	SmithGame game;
	GameWindow window(&game, "SmithGame", 1600, 900, 8, true);
	return window.Run(75);
}
