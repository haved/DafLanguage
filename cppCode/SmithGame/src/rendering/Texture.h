#pragma once

#include <string>
#include <GL/glew.h>

class Texture {
public:
    Texture(const std::string& filepath);
    ~Texture();
    void LoadTexture();
    void UnloadTexture();
    void Bind();
    inline bool HasPath(const std::string& filepath) {
        return m_filepath.compare(filepath) == 0;
    }
    inline bool Loaded() {
        return m_texture;
    }
private:
    const std::string& m_filepath;
    GLuint m_texture;
};

void LoadFromImage(const std::string& filepath, GLuint& address);
