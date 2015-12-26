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
	void LoadMeshData(Vertex vertices[], uint32_t vertexCount, uint32_t indices[], uint32_t indexCount);
	GLuint m_vbo;
	GLuint m_ibo;
	int m_indexCount;
};
