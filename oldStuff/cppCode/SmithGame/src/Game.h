#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Game {
public:
	virtual void Init()=0;
	virtual void NextFrame()=0;
	virtual void OnResize(int width, int height)=0;
	virtual void Destroy()=0;
	virtual void OnKeyEvent(int key, int action)=0;
	virtual void LoaderUpdate()=0;
};
