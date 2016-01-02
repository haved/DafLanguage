#pragma once

#include "Vertex.h"
#include <string>
#include <GL/glew.h>
#include <iostream>

class Mesh
{
public:
    Mesh(const std::string &filepath);
	~Mesh();
	void LoadMesh();
    void UnloadMesh();
	void Draw();
	inline bool HasFilepath(const std::string& path) {
        return m_filepath.compare(path)==0;
	}
	inline bool Loaded() {
        return m_loaded;
	}
private:
	const std::string m_filepath;
	bool m_loaded;
	GLuint m_vbo;
	GLuint m_ibo;
	uint32_t m_indexCount;
};

inline void DrawMesh(GLuint vbo, GLuint ibo, uint32_t indexCount);
