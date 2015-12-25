#pragma once

#include "Game.h"
#include <SDL2/SDL.h>

class GameWindow {
public:
	GameWindow(Game* game, const char* title, int width, int height, int samples, bool vsync);
	int Run(int frameRate);
	void UseRenderContext();
	void UseThreadContext();
	void SetToClose();
	inline bool StayGoing() {
        return m_stayGoing;
	}
	inline Game* GetGame() {
        return m_game;
	}
private:
	Game* m_game;
	const char* m_title;
	int m_width, m_height, m_samples;
	bool m_vsync;

	SDL_Window* m_window;
	SDL_GLContext m_threadContext;
	SDL_GLContext m_renderContext;
	bool m_stayGoing;
};
