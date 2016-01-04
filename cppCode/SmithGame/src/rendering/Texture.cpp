#include "Texture.h"

#include <SFML/Graphics/Image.hpp>
#include <GL/glew.h>

Texture::Texture(const std::string& filepath) : m_filepath(filepath), m_texture(0) {

}

Texture::~Texture() {
    UnloadTexture();
}

void Texture::LoadTexture() {
    if(m_texture)
        return;

    LoadFromImage(m_filepath, &m_texture);
}

void Texture::UnloadTexture() {
    if(!m_texture)
        return;

    glDeleteTextures(1, &m_texture);
    m_texture=0;
}

void Texture::Bind() {
    glBindTexture(GL_TEXTURE_2D, m_texture); //If it's 0 (unloaded), it will disable texturing.
}

void LoadFromImage(const std::string& filepath, GLuint* address) {
    sf::Image image;
    image.loadFromFile(filepath);
    unsigned int width  = image.getSize().x;
    unsigned int height = image.getSize().y;

    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    image.flipVertically();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());

    glFlush();
}
