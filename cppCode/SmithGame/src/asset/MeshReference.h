#pragma once
#include <inttypes.h>

class AssetSystem;

class MeshReference  {
    public:
        MeshReference(AssetSystem* assets, uint32_t meshId);
        ~MeshReference();
        void Draw();
    private:
        AssetSystem* m_assets;
        uint32_t m_meshId;
};
