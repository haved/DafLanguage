#include "MeshRaw.h"
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include "MeshPlybinLoader.h"

MeshRaw::MeshRaw(const std::string &filepath) : m_vbo(0), m_ibo(0), m_indexCount(0) {
    Vertex* vertices;
    uint32_t* indices;
    uint32_t vertexCount;
    uint32_t indexCount;

    AllocateDataFromPlybin(filepath, &vertices, &vertexCount, &indices, &indexCount);
    LoadMeshData(vertices, vertexCount, indices, indexCount);
    delete[] vertices;
    delete[] indices;
}

MeshRaw::MeshRaw(Vertex vertices[], uint32_t vertexCount, uint32_t indices[], uint32_t indexCount)
{
	LoadMeshData(vertices, vertexCount, indices, indexCount);
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

#include <SDL2/SDL.h>
void MeshRaw::LoadMeshData(Vertex vertices[], uint32_t vertexCount, uint32_t indices[], uint32_t indexCount)
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

void MeshRaw::Draw()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), NULL);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (void*)sizeof(glm::vec3));
	glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(glm::vec3)*2));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, NULL);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}
