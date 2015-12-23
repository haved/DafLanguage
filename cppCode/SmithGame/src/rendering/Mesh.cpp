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
    std::streampos memsize_pos = file.tellg();
    uint32_t memsize = (uint32_t) memsize_pos;
    file.seekg (0, std::ios::beg);

    uint32_t header_mem[2];
    uint32_t neededSize = sizeof(uint32_t)*2;
    if(memsize < neededSize) {
        std::cerr << "File " << filepath << " was less than 8 bytes long! Aborting!" << std::endl;
        assert(false);
    }
    file.read ((char*)header_mem, sizeof(uint32_t)*2);

    uint32_t vertexCount = header_mem[0];
    uint32_t indexCount = header_mem[1]*3;

    Vertex* vertices = new Vertex[vertexCount];
    neededSize += sizeof(Vertex) * vertexCount;
    if(memsize < neededSize) {
        std::cerr << "File " << filepath << " was not long engough for " << vertexCount << " vertices! Aborting!" << std::endl;
        assert(false);
    }
    file.read((char*)vertices, sizeof(Vertex)*vertexCount);

    uint32_t* indices = new uint32_t[indexCount];
    neededSize += sizeof(uint32_t) * indexCount;
    if(memsize < neededSize) {
        std::cerr << "File " << filepath << " was not long engough for " << indexCount << " indices! Aborting!" << std::endl;
        assert(false);
    }
    file.read((char*)indices, sizeof(uint32_t)*indexCount);

    std::cout << memsize << " / " << neededSize << std::endl;

    file.close();

    LoadMeshData(vertices, header_mem[0], indices, indexCount);

    delete[] vertices;
    delete[] indices;
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

	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), NULL);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (void*)sizeof(glm::vec3));
	glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(glm::vec3)*2));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glDrawElements(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_INT, NULL);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}
