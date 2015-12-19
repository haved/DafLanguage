#include "GameWindow.h"
#include "SmithGame.h"
#include "SDL_imp_fix.h"
#include <SDL.h>

void SmithGame::Init() {
	
}

void SmithGame::NextFrame() {

}

void SmithGame::OnResize(int width, int height) {

}

void SmithGame::Destroy() {

}

int main(int argc, char *argv[]) {
	SmithGame game;
	GameWindow window(&game, "SmithGame", 1600, 900, 8, true);
	return window.Run(75);
}