#include "GameWindow.h"
#include <iostream>
#include "Time.h"
#include <glm/glm.hpp>
#include <SDL2/SDL.h>

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
    GLFWwindow* threadContext = gameWindow->GetThreadContext();
    glfwMakeContextCurrent(threadContext);
    Game* game = gameWindow->GetGame();

    SDL_Delay(1000);
    while(!glfwWindowShouldClose(threadContext)) {
        game->LoaderUpdate();
        SDL_Delay(10);
    }
    std::cout << "Using NO context!" << std::endl;
    glfwMakeContextCurrent(NULL);
    return 0;
}

void error_callback(int error, const char* description) {
    puts(description);
}

int GameWindow::Run(int frameRate) {
	std::cout << "Running application!" << std::endl;

    //====================================================================INIT of SDL and GLFW
	if (SDL_Init(SDL_INIT_TIMER) < 0) {
		std::cerr << "SDL failed to Init! Aborting!" << std::endl;
		return -1;
	}
	glfwSetErrorCallback(error_callback);
    if(!glfwInit()) {
        std::cerr << "GLFW failed to init! Aborting!" << std::endl;
        exit(EXIT_FAILURE);
    }
    //====================================================================GLFW window creation
	glfwDefaultWindowHints();
    glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, m_samples);
    m_renderWindow = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
    if (!m_renderWindow) {
		std::cerr << "GLFW window creation failed!" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
    const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor()); //Center the renderWindow on the screen
    glfwSetWindowPos(m_renderWindow, (vidmode->width-m_width)/2, (vidmode->height-m_height)/2);
    m_threadWindow = glfwCreateWindow(0, 0, "ThreadWindow", NULL, m_renderWindow);
    if (!m_threadWindow) {
		std::cerr << "GLFW thread window creation failed!" << std::endl;
		glfwDestroyWindow(m_renderWindow);
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
    //====================================================================INIT of GLEW
	if(glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW!" << std::endl;
		glfwDestroyWindow(m_threadWindow);
		glfwDestroyWindow(m_renderWindow);
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

    //====================================================================GAME INIT and LOOP
	m_game->Init();
	m_game->OnResize(m_width, m_height);
    SDL_Thread* loaderThread = SDL_CreateThread(loadThread, "SmithGame_Loader_thread", (void*)this);//Making thread
    glfwShowWindow(m_renderWindow);
	while (!glfwWindowShouldClose(m_renderWindow)) {
        UpdateDeltaTime();
		m_game->NextFrame();
		glfwSwapBuffers(m_renderWindow);
		glfwPollEvents();
	}
	//====================================================================TELL and wait for the loading thread to stop,
    glfwSetWindowShouldClose(m_threadWindow, GL_TRUE);
    int threadReturnValue;
    SDL_WaitThread(loaderThread, &threadReturnValue);
    //====================================================================DESTROY everytning
    m_game->Destroy();
	glfwDestroyWindow(m_threadWindow);
	glfwDestroyWindow(m_renderWindow);
    glfwTerminate();
	SDL_Quit();

	return 0;
}
