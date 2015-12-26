#include "MeshReference.h"
#include "AssetSystem.h"

MeshReference::MeshReference(AssetSystem* assets, int meshId, int* countPtr) : m_assets(assets), m_meshId(meshId), m_countPtr(countPtr) {
    countPtr[0]++;
}

MeshReference::~MeshReference() {
    m_countPtr[0]--;
    if(*m_countPtr<=0) {
        delete m_countPtr;
    }
}

void MeshReference::Draw() {
    m_assets->DrawMesh(m_meshId);
}
