#include "GameWindow.h"
#include <iostream>
#include <GL/glew.h>
#include "Time.h"
#include <glm/glm.hpp>

GameWindow::GameWindow(Game * game, const char* title, int width, int height, int samples, bool vsync)
{
	m_game = game;
	m_title = title;
	m_width = width;
	m_height = height;
	m_samples = samples;
	m_vsync = vsync;
}

int loadThread(void* arg) {
    GameWindow* gameWindow = (GameWindow*) arg;
    while(gameWindow->StayGoing()) {
        gameWindow->GetGame()->LoaderUpdate();
        SDL_Delay(10);
    }
    return 0;
}

int GameWindow::Run(int frameRate) {
	std::cout << "Running application!" << std::endl;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cerr << "SDL failed to Init! Aborting!" << std::endl;
		return -1;
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	m_window = SDL_CreateWindow(m_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		m_width, m_height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (m_window == NULL) {
		std::cerr << "SDL window creation failed!" << std::endl;
		return -1;
	}
	SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1);
	m_threadContext = SDL_GL_CreateContext(m_window);
	m_renderContext = SDL_GL_CreateContext(m_window);

	if(glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW!" << std::endl;
		return -1;
	}

	m_game->Init();
	m_game->OnResize(m_width, m_height);

	m_stayGoing = true;
    SDL_Thread* loaderThread = SDL_CreateThread(loadThread, "SmithGame_Loader_thread", (void*)this);
	while (m_stayGoing) {
        UpdateDeltaTime();
		m_game->NextFrame();
		SDL_GL_SwapWindow(m_window);
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
				case SDL_QUIT: SetToClose(); break;
				case SDL_WINDOWEVENT: if (e.window.event == SDL_WINDOWEVENT_RESIZED)
										m_game->OnResize(e.window.data1, e.window.data2);
										break;
                case SDL_KEYDOWN:
                    m_game->OnKeyPressed(e.key.keysym.sym); break;
                case SDL_KEYUP:
                    m_game->OnKeyReleased(e.key.keysym.sym); break;
				default: break;
			}
		}
	}

	m_game->Destroy();

    int threadReturnValue;
    SDL_WaitThread(loaderThread, &threadReturnValue);
    SDL_GL_DeleteContext(m_threadContext);
	SDL_GL_DeleteContext(m_renderContext);
	SDL_DestroyWindow(m_window);

	SDL_Quit();

	return 0;
}

inline void GameWindow::SetToClose() {
	m_stayGoing = false;
}

inline void GameWindow::UseRenderContext() {
	SDL_GL_MakeCurrent(m_window, m_renderContext);
}

inline void GameWindow::UseThreadContext() {
    SDL_GL_MakeCurrent(m_window, m_threadContext);
}