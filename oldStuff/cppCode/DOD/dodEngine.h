#pragma once

struct Vector3 {
	float x;
	float y;
	float z;
};

struct GameState;
struct Entity;

struct Entity {
	Vector3 position;
	void (*updateFunc)(GameState*, Entity*, float);
	void (*renderFunc)(GameState*, Entity*);
	const char* name;
	bool alive;
};

#define MAX_ENTITY 20

struct EntityPool {
	Entity entities[MAX_ENTITY];
	int entityCount;
};

struct GameState {
	EntityPool entities;
	Entity *player;
	float playerSpeedX, playerSpeedY;
};
