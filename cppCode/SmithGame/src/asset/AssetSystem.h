#pragma once

#include <vector>
#include "../rendering/Mesh.h"
#include <memory>
#include "MeshReference.h"

class AssetSystem {
    public:
        int AddMeshAsset(const std::string& filepath);
        int GetMeshIdFromPath(const std::string& filepath);
        std::shared_ptr<MeshReference> LoadMesh(int meshId);
        void SetMeshToBeDeleted(int meshId);
        void DrawMesh(int meshId);
    private:
        std::vector<Mesh> m_meshClasses;
};
