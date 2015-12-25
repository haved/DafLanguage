#pragma once
#include <SDL2/SDL_keycode.h>

class Game {
public:
	virtual void Init()=0;
	virtual void NextFrame()=0;
	virtual void OnResize(int width, int height)=0;
	virtual void Destroy()=0;
	virtual void OnKeyPressed(SDL_Keycode code)=0;
	virtual void OnKeyReleased(SDL_Keycode code)=0;
	virtual void LoaderUpdate()=0;
};
