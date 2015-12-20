#pragma once
#include "Game.h"
#include "Scene.h"
#include <glm/glm.hpp>

class SmithGame : public Game {
public:
	void Init();
	void NextFrame();
	void OnResize(int width, int height);
	void Destroy();
private:
    Scene* scene;
    glm::mat4 projectionMatrix;
};
