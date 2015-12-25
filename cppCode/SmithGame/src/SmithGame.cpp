#include "GameWindow.h"
#include "SmithGame.h"
#include "scene/GameObject.h"
#include "game/TestComponent.h"
#include <GL/glew.h>
#include <memory>
#define  GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>
#include "Time.h"
#include "rendering/Mesh.h"
#include <iostream>

float FOV = 3.14159265f/2;
float TAU = 3.14159265f*2;

std::string SmithGame::RES_PATH="./res/";

void SmithGame::Init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.3f, 0.5f, 0.9f, 1);
    scene = new Scene();
    auto object = std::make_shared<GameObject>();
    auto mesh = std::make_shared<Mesh>(RES_PATH+"mesh/cubeThing.plybin");
    auto shader = std::make_shared<BasicShader>(RES_PATH+"shader/BasicShader.vs", RES_PATH+"shader/BasicShader.fs");
    shader->LoadToGPU();
    object->AddComponent(std::make_shared<TestComponent>(.8f, mesh,shader));
    scene->AddObject(object);
}

void SmithGame::Destroy() {
    delete scene;
}

void SmithGame::LoaderUpdate() {
    std::cout << "Second thread!" << std::endl;
}

bool w,a,s,d,pause=true;
glm::vec3 walkVector;
glm::vec3 camPos(0, 0, 10);
glm::vec3 camTarget(0, 0, 0);
void SmithGame::NextFrame() {
    camPos += walkVector*(GetDeltaTime()*30);
    if(!pause)
        scene->Update();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 view = glm::lookAt(camPos, camTarget, glm::vec3(0, 1, 0));
    scene->Render(projectionMatrix*view);
}

void SmithGame::OnResize(int width, int height) {
    glViewport(0, 0, width, height);
    projectionMatrix = glm::perspectiveFov(FOV, (float)width, (float)height, 0.1f, 200.f);
}

void SmithGame::OnKeyPressed(SDL_Keycode code) {
    switch(code) {
        case SDLK_w: w=true; break;
        case SDLK_a: a=true; break;
        case SDLK_s: s=true; break;
        case SDLK_d: d=true; break;
        case SDLK_SPACE: pause=!pause; break;
        default: break;
    }
    int x = 0;
    int y = 0;
    if(w)
        y++;
    if(a)
        x--;
    if(s)
        y--;
    if(d)
        x++;
    walkVector = glm::vec3(x, y, 0);
}

void SmithGame::OnKeyReleased(SDL_Keycode code) {
    switch(code) {
        case SDLK_w: w=false; break;
        case SDLK_a: a=false; break;
        case SDLK_s: s=false; break;
        case SDLK_d: d=false; break;
        default: break;
    }
    int x = 0;
    int y = 0;
    if(w)
        y++;
    if(a)
        x--;
    if(s)
        y--;
    if(d)
        x++;
    walkVector = glm::vec3(x, y, 0);
}

int main(int argc, char *argv[]) {
	SmithGame game;
	GameWindow window(&game, "SmithGame", 1600, 900, 8, true);
	return window.Run(75);
}
