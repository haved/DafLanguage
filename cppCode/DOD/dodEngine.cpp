#include "dodEngine.h"
#include <iostream>

void InitEntityPool(EntityPool *pool) {
	pool->entityCount = 0;
}

void InitGameState(GameState *state) {
	InitEntityPool(&state->entities);
}

void updatePlayer(GameState *state, Entity *entity, float deltaTime) {
	entity->position.x+=state->playerSpeedX;
	entity->position.y+=state->playerSpeedY;
}

void renderPlayer(GameState *state, Entity* entity) {
	std::cout << "Player at x:" << entity->position.x << 
						", y:" << entity->position.y << std::endl;
}

void updateTree(GameState *state, Entity* entity, float deltaTime)
{
	if(state->player->position.x > entity->position.x || 
			state->player->position.y > entity->position.y)
 		entity->alive=false;
}

void renderTree(GameState* state, Entity* entity) {
	std::cout << "Tree at x: " << entity->position.x << 
						", y:" << entity->position.y << std::endl;
}

void SetVector(Vector3 &vector, float x, float y, float z) {
	vector.x = x;
	vector.y = y;
	vector.z = z;
}

void InitPlayer(Entity *player) {
	player->name = "The Player";
	player->updateFunc = &updatePlayer;
	player->renderFunc = &renderPlayer;
	player->alive = true;
	SetVector(player->position, 0, 0, 0);
}

void InitTree(Entity *tree, float x, float y, float z) {
	tree->name = "Tree";
	tree->updateFunc = &updateTree;
	tree->renderFunc = &renderTree;
	tree->alive = true;
	SetVector(tree->position, x, y, z);
}

Entity* AddEntity(EntityPool *pool) {
	return &pool->entities[pool->entityCount++];
}

void RemoveEntity(EntityPool *pool, int index) {
	pool->entities[index] = pool->entities[--pool->entityCount];
}

void runEngine() {
	GameState state;
	InitGameState(&state);

	state.player = AddEntity(&state.entities);
	InitPlayer(state.player);

	state.playerSpeedX = 1;
	state.playerSpeedY = 1;

	for(int i = 0; i < 10; i++) {
		InitTree(AddEntity(&state.entities), i * 4+2, i * 3 + 7, 0);
	}

	//By now, everything is on the stack and in state. Good?
	
	while(state.entities.entityCount > 1) {

		std::cout << "Update!" << std::endl;
		for(int i = 0; i < state.entities.entityCount; i++)
			state.entities.entities[i].updateFunc(&state, &state.entities.entities[i], 0.3f);
		
		std::cout << "Removal of dead trees!" << std::endl;
		for(int i = 0; i < state.entities.entityCount; i++)
			if(!state.entities.entities[i].alive)
				RemoveEntity(&state.entities, i);

		std::cout << "Rendering!" << std::endl;
		for(int i = 0; i < state.entities.entityCount; i++)
			state.entities.entities[i].renderFunc(&state, &state.entities.entities[i]);
	
		std::cout << "Entities left: " << state.entities.entityCount << std::endl <<
		"Press any key to continue!" << std::endl;
		std::cin.get();
	}
	std::cout << "You have cut down the whole wood. Hope you're happy. D:" << std::endl;	
}

int main(int argc, char** argv) {
	runEngine();
}