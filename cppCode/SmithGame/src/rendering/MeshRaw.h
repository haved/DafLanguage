#pragma once

#include "Vertex.h"
#include <string>
#include <GL/glew.h>

class MeshRaw
{
public:
    MeshRaw(const std::string &filepath);
	MeshRaw(Vertex vertices[], uint32_t vertexCount, uint32_t indices[], uint32_t indexCount);
	~MeshRaw();
	void Draw();
private:
	GLuint m_vbo;
	GLuint m_ibo;
	uint32_t m_indexCount;
};
