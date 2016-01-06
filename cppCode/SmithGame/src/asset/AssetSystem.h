#pragma once

#include <vector>
#include "../rendering/Mesh.h"
#include "../rendering/Texture.h"
#include <memory>
#include "MeshReference.h"
#include "TextureReference.h"

class AssetSystem {
    public:
        AssetSystem();
        uint32_t AddMeshAsset(const std::string& filepath);
        uint32_t GetMeshIdFromPath(const std::string& filepath);
        std::shared_ptr<MeshReference> LoadMesh(uint32_t meshId);
        void OnMeshReferenceRemoved(uint32_t meshId);
        inline Mesh* GetLoadedMeshClass(uint32_t meshId) {
            return &m_meshClasses[meshId];
        }
        uint32_t AddTextureAsset(const std::string& filepath);
        uint32_t GetTextureIdFromPath(const std::string& filepath);
        std::shared_ptr<TextureReference> LoadTexture(uint32_t textureId);
        std::shared_ptr<TextureReference> NullTexture();
        void OnTextureReferenceRemoved(uint32_t textureId);
        inline Texture* GetLoadedTextureClass(uint32_t textureId) {
            return &m_textureClasses[textureId];
        }

        void DoAllLoading();
    private:
        std::vector<Mesh> m_meshClasses;
        std::vector<uint32_t> m_meshReferenceCounts;
        std::vector<uint32_t> m_meshLoadStack;
        std::vector<uint32_t> m_meshUnloadStack;

        std::vector<Texture> m_textureClasses;
        std::vector<uint32_t> m_textureReferenceCounts;
        std::vector<uint32_t> m_textureLoadStack;
        std::vector<uint32_t> m_textureUnloadStack;
};
