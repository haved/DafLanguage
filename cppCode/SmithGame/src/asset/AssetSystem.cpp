#include "AssetSystem.h"

AssetSystem::AssetSystem() : m_meshClasses({}), m_meshReferenceCounts({}), m_loadStack({}), m_unloadStack({}) {

}

uint32_t AssetSystem::AddMeshAsset(const std::string& filepath) {
    m_meshReferenceCounts.push_back(0);
    m_meshClasses.push_back(Mesh(filepath));
    return m_meshClasses.size()-1;
}

uint32_t AssetSystem::GetMeshIdFromPath(const std::string& filepath) {
    for(uint32_t i = 0; i < m_meshClasses.size(); i++) {
        if(m_meshClasses[i].HasFilepath(filepath))
            return i;
    }
    return 0xFFFFFFFF;
}

std::shared_ptr<MeshReference> AssetSystem::LoadMesh(uint32_t meshId) {
    if(m_meshReferenceCounts[meshId]<=0)
        m_loadStack.push_back(meshId);
    m_meshReferenceCounts[meshId]++;
    return std::make_shared<MeshReference>(this, meshId);
}

void AssetSystem::OnReferenceRemoved(uint32_t meshId) {
    m_meshReferenceCounts[meshId]--;
    if(m_meshReferenceCounts[meshId]<=0) {
        m_unloadStack.push_back(meshId);
    }
}

void AssetSystem::DoAllLoading() {
    while(m_unloadStack.size() > 0) {
        m_meshClasses[m_unloadStack.back()].UnloadMesh();
        m_unloadStack.pop_back();
    }
    while(m_loadStack.size() > 0) {
        m_meshClasses[m_loadStack.back()].LoadMesh();
        m_loadStack.pop_back();
    }
}
