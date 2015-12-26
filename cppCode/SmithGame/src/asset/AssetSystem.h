#pragma once

#include <vector>
#include "../rendering/Mesh.h"
#include <memory>
#include "MeshReference.h"

class AssetSystem {
    public:
        AssetSystem();
        uint32_t AddMeshAsset(const std::string& filepath);
        uint32_t GetMeshIdFromPath(const std::string& filepath);
        std::shared_ptr<MeshReference> LoadMesh(uint32_t meshId);
        void OnReferenceRemoved(uint32_t meshId);
        inline Mesh* GetLoadedMeshClass(uint32_t meshId) {
            return &m_meshClasses[meshId];
        }
        void DoAllLoading();
    private:
        std::vector<Mesh> m_meshClasses;
        std::vector<uint32_t> m_meshReferenceCounts;
        std::vector<uint32_t> m_loadStack;
        std::vector<uint32_t> m_unloadStack;
};
