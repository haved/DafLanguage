#pragma once

#include "Vertex.h"
#include <string>
#include <GL/glew.h>

class Mesh
{
public:
    Mesh(const std::string &filepath);
	~Mesh();
	void LoadMesh();
    void UnloadMesh();
	void Draw();
private:
	const std::string m_filepath;
	bool m_loaded;
	GLuint m_vbo;
	GLuint m_ibo;
	uint32_t m_indexCount;
};
