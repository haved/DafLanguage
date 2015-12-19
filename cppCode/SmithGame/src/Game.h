#pragma once

class Game {
public:
	virtual void Init()=0;
	virtual void NextFrame()=0;
	virtual void OnResize(int width, int height)=0;
	virtual void Destroy()=0;
};