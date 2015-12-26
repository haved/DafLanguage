#pragma once

#include <glm/glm.hpp>

struct Vertex {
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec3 color;
	Vertex()
	{
		color = glm::vec3(1, 1, 1);
		normal = glm::vec3(0, 0, 1);
	}
	Vertex(float x, float y, float z)
	{
		pos.x = x;
		pos.y = y;
		pos.z = z;
		color = glm::vec3(1, 1, 1);
		normal = glm::vec3(0, 0, 1);
	}
	Vertex(float x, float y, float z, float r, float g, float b)
	{
		pos.x = x;
		pos.y = y;
		pos.z = z;
		color.x = r;
		color.y = g;
		color.z = b;
		normal = glm::vec3(0, 0, 1);
	}
	Vertex(float x, float y, float z, float nx, float ny, float nz, float r, float g, float b)
	{
		pos.x = x;
		pos.y = y;
		pos.z = z;
		color.x = r;
		color.y = g;
		color.z = b;
		normal.x = nx;
		normal.y = ny;
		normal.z = nz;
	}
};

typedef struct Vertex Vertex;

