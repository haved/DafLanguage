#pragma once
#include "Game.h"
#include "scene/Scene.h"
#include <glm/glm.hpp>

class SmithGame : public Game {
public:
    static std::string RES_PATH;
	void Init();
	void NextFrame();
	void OnResize(int width, int height);
	void Destroy();
	virtual void OnKeyPressed(SDL_Keycode code);
	virtual void OnKeyReleased(SDL_Keycode code);
private:
    //void funkyBoxes();
    Scene* scene;
    glm::mat4 projectionMatrix;
};
