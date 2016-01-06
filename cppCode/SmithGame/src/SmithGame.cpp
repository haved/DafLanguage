#include "GameWindow.h"
#include "SmithGame.h"
#include "scene/GameObject.h"
#include "game/TestComponent.h"
#include <GL/glew.h>
#include <memory>
#define  GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>
#include "Time.h"
#include "rendering/TextureRaw.h"
#include <iostream>
#include "common.h"

float FOV = PI/2; //Ninety degrees

std::string SmithGame::RES_PATH="../res/";

void SmithGame::Init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.3f, 0.5f, 0.9f, 1);
    scene  = new Scene();
    assets = new AssetSystem();
    int terrainMesh = assets->AddMeshAsset(RES_PATH+"mesh/Terrain.plybin11");
    int treeMesh    = assets->AddMeshAsset(RES_PATH+"mesh/Tree9.plybin11");
    int treeTexture = assets->AddTextureAsset(RES_PATH+"texture/Tree9.png");

    auto shader       = std::make_shared<BasicShader>(RES_PATH+"shader/BasicShader120.vs", RES_PATH+"shader/BasicShader120.fs");
    shader->LoadToGPU();

    auto terrainObject=std::make_shared<GameObject>();
    terrainObject->AddComponent(std::make_shared<TestComponent>(0, assets->LoadMesh(terrainMesh), assets->LoadTexture(treeTexture), shader));
    scene->AddObject(terrainObject);

    auto treeObject = std::make_shared<GameObject>();
    treeObject->AddComponent(std::make_shared<TestComponent>(0, assets->LoadMesh(treeMesh), assets->NullTexture(), shader));
    treeObject->GetMutPosPointer()->z=0.2f;
    treeObject->GetMutRotPointer()->z=PI/2;
    scene->AddObject(treeObject);
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
    camTarget += walkVector*(GetDeltaTime()*8);
    camPos=camTarget+glm::vec3(0, -4, 10);
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
    if((action!=GLFW_PRESS) & (action!=GLFW_RELEASE))
        return;
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

    walkVector=glm::vec3(a?-1:(d?1:0),w?1:(s?-1:0),0);
}

int main(int argc, char *argv[]) {
	SmithGame game;
	GameWindow window(&game, "SmithGame", 1600, 900, 8, false);
	return window.Run(75);
}
