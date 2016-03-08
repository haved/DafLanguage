#include "TextureRaw.h"

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <GL/glew.h>

TextureRaw::TextureRaw(const std::string& filepath) : m_texture(0) {
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

TextureRaw::TextureRaw() {
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    int pixel = 0xFFFFFFFF;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixel);
}

TextureRaw::~TextureRaw() {
    glDeleteTextures(1, &m_texture);
}

void TextureRaw::Bind() {
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

void UseNoTexture() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
