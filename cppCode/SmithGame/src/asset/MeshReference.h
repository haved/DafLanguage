#pragma once

class AssetSystem;

class MeshReference  {
    public:
        MeshReference(AssetSystem* assets, int meshId, int* countPtr);
        ~MeshReference();
        void Draw();
    private:
        AssetSystem* m_assets;
        int m_meshId;
        int* m_countPtr;
};
