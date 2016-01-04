#pragma once

#include <string>
#include "Vertex.h"
#include <GL/glew.h>

void AllocateDataFromPlybin(const std::string& filepath, Vertex** vertices, uint32_t* vertexCount, uint32_t** indices, uint32_t* indexCount);
void AllocateGLMeshFromPlybin(const std::string& filepath, GLuint* vbo, GLuint* ibo, uint32_t* indexCount);
