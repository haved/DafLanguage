#include "GameWindow.h"
#include <iostream>
#include "Time.h"
#include <glm/glm.hpp>
#include <SDL2/SDL.h>

GameWindow* GameWindow::instance=NULL;

GameWindow::GameWindow(Game* game, const char* title, int width, int height, int samples, bool vsync)
{
    GameWindow::instance=this;
	m_game = game;
	m_title = title;
	m_width = width;
	m_height = height;
	m_samples = samples;
	m_vsync = vsync;
}

int loadThread(void* arg) {
    GameWindow* gameWindow = GameWindow::instance;
    GLFWwindow* threadContext = gameWindow->GetThreadContext();
    glfwMakeContextCurrent(threadContext);
    Game* game = gameWindow->GetGame();

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

void window_resize_callback(GLFWwindow* window, int width, int height) {
    GameWindow::instance->GetGame()->OnResize(width, height);
}

void window_keyevent_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    GameWindow::instance->GetGame()->OnKeyEvent(key, action);
}

int GameWindow::Run(uint32_t frameRate) {
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
    //====================================================================GLFW render window window creation
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
    //=====================================Render window callbacks
    glfwSetWindowSizeCallback(m_renderWindow, window_resize_callback);
    glfwSetKeyCallback(m_renderWindow, window_keyevent_callback);
    //=====================================Thread window
    m_threadWindow = glfwCreateWindow(80, 60, "ThreadWindow", NULL, m_renderWindow);
    if (!m_threadWindow) {
		std::cerr << "GLFW thread window creation failed!" << std::endl;
		glfwDestroyWindow(m_renderWindow);
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
    //====================================================================INIT of GLEW
    glfwMakeContextCurrent(m_renderWindow);

    glewExperimental=true;
    GLenum err = glewInit();
	if(err!=GLEW_OK) {
		std::cerr << "Failed to initialize GLEW!" << glewGetErrorString(err) << std::endl;
		glfwDestroyWindow(m_threadWindow);
		glfwDestroyWindow(m_renderWindow);
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

    //====================================================================GAME INIT and LOOP
	m_game->Init();
	m_game->OnResize(m_width, m_height);
    SDL_Thread* loaderThread = SDL_CreateThread(loadThread, "SmithGame_Loader_thread", NULL);//Making thread
    glfwShowWindow(m_renderWindow);
    uint32_t startMs = SDL_GetTicks();
    uint32_t framesAgo = 0;
    float msPerFrame = 1000.f/frameRate;
	while (!glfwWindowShouldClose(m_renderWindow)) {
        UpdateDeltaTime();
		m_game->NextFrame();
		glfwSwapBuffers(m_renderWindow);
		glfwPollEvents();
        framesAgo++;
        uint32_t wantedTime = startMs+((uint32_t)(framesAgo*msPerFrame));
        uint32_t currentTime = SDL_GetTicks();
        if(wantedTime>currentTime)
            SDL_Delay(wantedTime-currentTime);
        if(framesAgo>=frameRate) {
            framesAgo=0;
            startMs+=1000;
        }
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
    std::cout << "Program end" << std::endl;
	return 0;
}
