#include "MeshReference.h"
#include "AssetSystem.h"

MeshReference::MeshReference(AssetSystem* assets, uint32_t meshId) : m_assets(assets), m_meshId(meshId) {
}

MeshReference::~MeshReference() {
    m_assets->OnMeshReferenceRemoved(m_meshId);
}

void MeshReference::Draw() {
    m_assets->GetLoadedMeshClass(m_meshId)->Draw();
}

bool MeshReference::Loaded() {
    return m_assets->GetLoadedMeshClass(m_meshId)->Loaded();
}
