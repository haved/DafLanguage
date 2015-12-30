#include "GameWindow.h"
#include "SmithGame.h"
#include "scene/GameObject.h"
#include "game/TestComponent.h"
#include <GL/glew.h>
#include <memory>
#define  GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>
#include "Time.h"
#include "rendering/MeshRaw.h"
#include <iostream>
#include "common.h"

float FOV = PI/2; //Ninety degrees

std::string SmithGame::RES_PATH="../res/";

void SmithGame::Init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.3f, 0.5f, 0.9f, 1);
    scene  = new Scene();
    assets = new AssetSystem();
    int mesh = assets->AddMeshAsset(RES_PATH+"mesh/cubeThing.plybin");
    auto shader = std::make_shared<BasicShader>(RES_PATH+"shader/BasicShader120.vs", RES_PATH+"shader/BasicShader120.fs");
    shader->LoadToGPU();

    auto prevObject = std::make_shared<GameObject>();
    glm::vec3* scale = prevObject->GetMutScalePointer();
    scale->x=0.2f;
    scale->y=0.2f;
    scale->z=0.2f;
    scene->AddObject(prevObject);
    for(int i = 0; i<40; i++) {
        auto newObject=std::make_shared<GameObject>();
        newObject->AddComponent(std::make_shared<TestComponent>(.5f, assets->LoadMesh(mesh), shader));
        glm::vec3* posPointer = newObject->GetMutPosPointer();
        posPointer->z=4;
        posPointer->x=1;
        posPointer->y=-1;
        prevObject->AddChild(newObject);
        prevObject=newObject;
    }

    /*auto object = std::make_shared<GameObject>();
    object->AddComponent(std::make_shared<TestComponent>(.2f,assets->LoadMesh(mesh),shader));
    auto object2 = std::make_shared<GameObject>();
    object2->AddComponent(std::make_shared<TestComponent>(.8f, assets->LoadMesh(mesh), shader));

    object->AddChild(object2);
    scene->AddObject(object);*/
}

void SmithGame::Destroy() {
    delete scene;
    delete assets;//Oh boy!
}

void SmithGame::LoaderUpdate() {
    assets->DoAllLoading();
}

bool w,a,s,d,pause=false;
glm::vec3 walkVector;
glm::vec3 camPos(0, 0, 10);
glm::vec3 camTarget(0, 0, 0);

void SmithGame::NextFrame() {
    camPos += walkVector*(GetDeltaTime()*30);
    if(!pause) {
        UpdateIngameTime();
        scene->Update();
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 view = glm::lookAt(camPos, camTarget, glm::vec3(0, 1, 0));
    scene->Render(projectionMatrix*view);
    m_fpsCounter.NextFrame();
}

void SmithGame::OnResize(int width, int height) {
    glViewport(0, 0, width, height);
    projectionMatrix = glm::perspectiveFov(FOV, (float)width, (float)height, 0.1f, 200.f);
}

void SmithGame::OnKeyEvent(int key, int action) {
    if(key==GLFW_KEY_W)
        w=action==GLFW_PRESS;
    else if(key==GLFW_KEY_A)
        a=action==GLFW_PRESS;
    else if(key==GLFW_KEY_S)
        s=action==GLFW_PRESS;
    else if(key==GLFW_KEY_D)
        d=action==GLFW_PRESS;
    else if((key==GLFW_KEY_SPACE) & (action==GLFW_PRESS))
        pause=!pause;
}

int main(int argc, char *argv[]) {
	SmithGame game;
	GameWindow window(&game, "SmithGame", 1600, 900, 8, false);
	return window.Run(75);
}
