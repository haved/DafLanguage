#include "GameWindow.h"
#include "SmithGame.h"
#include "GameObject.h"
#include "game/TestComponent.h"
#include <GL/glew.h>
#include <memory>

void SmithGame::Init() {
    glClearColor(0.3f, 0.5f, 0.9f, 1);
    scene = new Scene();
    GameObject object;
    object.AddComponent(std::make_shared<TestComponent>(1.f));
    object.AddComponent(std::make_shared<TestComponent>(2.f));
    scene->AddObject(object);
}

void SmithGame::NextFrame() {
    scene->Update();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    scene->Render(projectionMatrix);
}

void SmithGame::OnResize(int width, int height) {
    glViewport(0, 0, width, height);
    projectionMatrix = glm::mat4(1.f);
}

void SmithGame::Destroy() {
    delete scene;
}

int main(int argc, char *argv[]) {
	SmithGame game;
	GameWindow window(&game, "SmithGame", 1600, 900, 8, true);
	return window.Run(75);
}
