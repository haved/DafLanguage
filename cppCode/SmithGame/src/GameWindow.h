#pragma once

#include "Game.h"
#include "GL/glew.h"
#include <GLFW/glfw3.h>

class GameWindow {
public:
	GameWindow(Game* game, const char* title, int width, int height, int samples, bool vsync);
	int Run(int frameRate);
	inline GLFWwindow* GetRenderContext() {
        return m_renderWindow;
	}
	inline GLFWwindow* GetThreadContext() {
        return m_threadWindow;
	}
	void SetToClose();
	inline Game* GetGame() {
        return m_game;
	}
private:
	Game* m_game;
	const char* m_title;
	int m_width, m_height, m_samples;
	bool m_vsync;

	GLFWwindow* m_renderWindow;
	GLFWwindow* m_threadWindow;
};
