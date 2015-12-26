#pragma once
#include "Game.h"
#include "scene/Scene.h"
#include <glm/glm.hpp>
#include "asset/AssetSystem.h"

class SmithGame : public Game {
public:
    static std::string RES_PATH;
	void Init();
	void NextFrame();
	void OnResize(int width, int height);
	void Destroy();
	void OnKeyPressed(SDL_Keycode code);
	void OnKeyReleased(SDL_Keycode code);
    void LoaderUpdate();
private:
    Scene* scene;
    AssetSystem* assets;
    glm::mat4 projectionMatrix;
};
