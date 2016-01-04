#include "MeshRaw.h"
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include "MeshPlybinLoader.h"
#include "Mesh.h"

MeshRaw::MeshRaw(const std::string &filepath) : m_vbo(0), m_ibo(0), m_indexCount(0) {
    AllocateGLMeshFromPlybin(filepath, &m_vbo, &m_ibo, &m_indexCount);
}

MeshRaw::MeshRaw(Vertex vertices[], uint32_t vertexCount, uint32_t indices[], uint32_t indexCount)
{
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);

	std::cout << "Allocated mesh with vbo: " << m_vbo << std::endl;
	m_indexCount = indexCount;
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertexCount, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t)*indexCount, indices, GL_STATIC_DRAW);
}

MeshRaw::~MeshRaw()
{
	if (m_indexCount != 0)
	{
        std::cout << "Deleted mesh with vbo: " << m_vbo << std::endl;
		glDeleteBuffers(1, &m_vbo);
		glDeleteBuffers(1, &m_ibo);
	}
}

void MeshRaw::Draw()
{
	DrawMesh(m_vbo, m_ibo, m_indexCount);
}
