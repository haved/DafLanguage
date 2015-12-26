#include "MeshPlybinLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>

void AllocateDataFromPlybin(const std::string& filepath, Vertex** vertices, uint32_t* vertexCount, uint32_t** indices, uint32_t* indexCount) {
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

    *vertexCount = header_mem[0];
    *indexCount = header_mem[1]*3;

    vertices[0] = new Vertex[*vertexCount];
    neededSize += sizeof(Vertex) * vertexCount[0];
    if(memsize < neededSize) {
        std::cerr << "File " << filepath << " was not long engough for " << vertexCount << " vertices! Aborting!" << std::endl;
        assert(false);
    }
    file.read((char*)vertices[0], sizeof(Vertex)* vertexCount[0]);

    indices[0] = new uint32_t[*indexCount];
    neededSize += sizeof(uint32_t) * indexCount[0];
    if(memsize < neededSize) {
        std::cerr << "File " << filepath << " was not long engough for " << indexCount << " indices! Aborting!" << std::endl;
        assert(false);
    }
    file.read((char*)indices[0], sizeof(uint32_t)* indexCount[0]);

    if(memsize!=neededSize) {
        std::clog << "Warning: The mesh file " << filepath << " was longer than specified in it's header! " << neededSize << "/" << memsize << std::endl;
    }

    file.close();
}

