#pragma once

#include <string>
#include "Vertex.h"

void AllocateDataFromPlybin(const std::string& filepath, Vertex** vertices, uint32_t* vertexCount, uint32_t** indices, uint32_t* indexCount);
