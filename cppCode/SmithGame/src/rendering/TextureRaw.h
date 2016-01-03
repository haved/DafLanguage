#pragma once

#include <string>
#include <GL/glew.h>

class TextureRaw {
public:
    TextureRaw();
    TextureRaw(const std::string& filepath);
    ~TextureRaw();
    void Bind();
private:
    GLuint m_texture;
};

void UseNoTexture();
