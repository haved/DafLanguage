#include "TextureReference.h"
#include "AssetSystem.h"
#include <GL/glew.h>

TextureReference::TextureReference(AssetSystem* assets, uint32_t textureId) : m_assets(assets), m_textureId(textureId) {
}

TextureReference::~TextureReference() {
    m_assets->OnTextureReferenceRemoved(m_textureId);
}

void TextureReference::Bind() {
    m_assets->GetLoadedTextureClass(m_textureId)->Bind();
}

bool TextureReference::Loaded() {
    return m_assets->GetLoadedTextureClass(m_textureId)->Loaded();
}
