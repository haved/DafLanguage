#pragma once

#include <inttypes.h>

class AssetSystem;

class TextureReference {
public:
    TextureReference(AssetSystem* assets, uint32_t textureId);
    ~TextureReference();
    void Bind();
    bool Loaded();
private:
    AssetSystem* m_assets;
    uint32_t m_textureId;
};
