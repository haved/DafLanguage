#pragma once
#include <inttypes.h>

class AssetSystem;

class MeshReference  {
    public:
        MeshReference(AssetSystem* assets, uint32_t meshId);
        ~MeshReference();
        void Draw();
        inline bool Loaded();
    private:
        AssetSystem* m_assets;
        uint32_t m_meshId;
};
