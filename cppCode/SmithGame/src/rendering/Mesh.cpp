#include "Mesh.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

Mesh::Mesh(const std::string &filepath) {
    std::ifstream file (filepath.c_str(), std::ios::in|std::ios::binary|std::ios::ate);
    if(!file.is_open()) {
        std::cerr << "Filed to open file " << filepath << "! Aborting!" << std::endl;
        assert(false);
    }
    std::streampos memsize = file.tellg();
    auto memblock = new char [size];
    file.seekg (0, std::ios::beg);
    file.read (memblock, size);
    file.close();

    if(memsize < 7) {
        std::cerr << "File " << filepath << " was less than 7 bytes long! Aborting!" << std::endl;
        assert(false);
    }
    uint32_t vertexCount = *((uint32_t*)&memblock[0]);
    uint32_t faceCount = *((uint32_t*)&memblock[4]);

    std::cout << "vertexCount=" << vertexCount << std::endl;
    std::cout << "faceCount=" << faceCount << std::endl;

    delete[] memblock;
}

Mesh::Mesh(Vertex vertices[], uint32_t vertexCount, uint32_t indices[], uint32_t indexCount)
{
	LoadMeshData(vertices, vertexCount, indices, indexCount);
}

Mesh::~Mesh()
{
	if (m_indicesCount != 0)
	{
        std::cout << "Deleted mesh with vbo: " << m_vbo << std::endl;
		glDeleteBuffers(1, &m_vbo);
		glDeleteBuffers(1, &m_ibo);
	}
}

void Mesh::LoadMeshData(Vertex vertices[], uint32_t vertexCount, uint32_t indices[], uint32_t indexCount)
{
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);

	std::cout << "Allocated mesh with vbo: " << m_vbo << std::endl;

	m_indicesCount = indexCount;

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertexCount, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t)*indexCount, indices, GL_STATIC_DRAW);
}

void Mesh::Draw()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (void*)sizeof(glm::vec3));
	glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(glm::vec3)*2));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glDrawElements(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}
