#include "GameWindow.h"
#include "SmithGame.h"
#include "GameObject.h"
#include "game/TestComponent.h"
#include <GL/glew.h>
#include <memory>
#define  GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>

float FOV = 3.14159265f/2;

void SmithGame::Init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.3f, 0.5f, 0.9f, 1);
    scene = new Scene();
    std::shared_ptr<GameObject> object = std::make_shared<GameObject>();
    object->GetMutPosPointer()->z+=3;
    object->AddComponent(std::make_shared<TestComponent>(1.f));
    scene->AddObject(object);
    std::shared_ptr<GameObject> object2 = std::make_shared<GameObject>();
    object2->GetMutPosPointer()->x+=3;
    object2->AddComponent(std::make_shared<TestComponent>(0));
    object->AddChild(object2);
}

glm::vec3 camPos(0, -5, 5);
glm::vec3 camTarget(0, 0, 0);
void SmithGame::NextFrame() {
    scene->Update();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 view = glm::lookAt(camPos, camTarget, glm::vec3(0, 1, 0));
    scene->Render(projectionMatrix*view);
}

void SmithGame::OnResize(int width, int height) {
    glViewport(0, 0, width, height);
    projectionMatrix = glm::perspectiveFov(FOV, (float)width, (float)height, 0.1f, 100.f);
}

void SmithGame::Destroy() {
    delete scene;
}

int main(int argc, char *argv[]) {
	SmithGame game;
	GameWindow window(&game, "SmithGame", 1600, 900, 8, true);
	return window.Run(75);
}
