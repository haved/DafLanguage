#pragma once
#include "Game.h"

class SmithGame : public Game {
public:
	void Init();
	void NextFrame();
	void OnResize(int width, int height);
	void Destroy();
};