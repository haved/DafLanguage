#include "Mesh.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "MeshPlybinLoader.h"

Mesh::Mesh(const std::string &filepath) : m_filepath(filepath), m_loaded(false), m_vbo(0), m_ibo(0), m_indexCount(0) {

}

Mesh::~Mesh()
{
	UnloadMesh();
}

void Mesh::LoadMesh() {
    if(m_loaded)
        return;

    glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);
    m_loaded = true;

    std::cout << "Allocated mesh with vbo: " << m_vbo << std::endl;

    Vertex* vertices;
    uint32_t* indices;
    uint32_t vertexCount;

    AllocateDataFromPlybin(m_filepath, &vertices, &vertexCount, &indices, &m_indexCount);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertexCount, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t)*m_indexCount, indices, GL_STATIC_DRAW);

	delete[] vertices;
	delete[] indices;
}

void Mesh::UnloadMesh() {
    if(!m_loaded)
        return;

    std::cout << "Deleted mesh with vbo: " << m_vbo << std::endl;
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ibo);

    m_loaded=false;
}

void Mesh::Draw() {
    if(!m_loaded)
        return;
    DrawMesh(m_vbo, m_ibo, m_indexCount);
}

inline void DrawMesh(GLuint vbo, GLuint ibo, uint32_t indexCount)
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), NULL);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(float)*3));
	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(float)*6));
	glVertexAttribPointer(3, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(float)*8));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, NULL);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
}
