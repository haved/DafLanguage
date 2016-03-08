#pragma once

#include <glm/glm.hpp>

struct Vertex {
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec2 texCoord;
	glm::vec3 color;
};

typedef struct Vertex Vertex;

