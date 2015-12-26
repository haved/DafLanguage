#include "MeshReference.h"
#include "AssetSystem.h"

MeshReference::MeshReference(AssetSystem* assets, uint32_t meshId) : m_assets(assets), m_meshId(meshId) {
}

MeshReference::~MeshReference() {
    m_assets->OnReferenceRemoved(m_meshId);
}

inline void MeshReference::Draw() {
    m_assets->GetLoadedMeshClass(m_meshId)->Draw();
}
