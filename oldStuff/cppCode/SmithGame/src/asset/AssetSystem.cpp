#include "AssetSystem.h"

#include <iostream>

AssetSystem::AssetSystem() : m_meshClasses({}), m_meshReferenceCounts({}), m_meshLoadStack({}), m_meshUnloadStack({}),
m_textureClasses({}), m_textureReferenceCounts({}), m_textureLoadStack({}), m_textureUnloadStack({}) {

    m_textureClasses.push_back(Texture());
    m_textureReferenceCounts.push_back(0);

    std::cout << "Asset system created!" << std::endl;
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
        m_meshLoadStack.push_back(meshId);
    m_meshReferenceCounts[meshId]++;
    return std::make_shared<MeshReference>(this, meshId);
}

void AssetSystem::OnMeshReferenceRemoved(uint32_t meshId) {
    m_meshReferenceCounts[meshId]--;
    if(m_meshReferenceCounts[meshId]<=0) {
        m_meshUnloadStack.push_back(meshId);
    }
}

uint32_t AssetSystem::AddTextureAsset(const std::string& filepath) {
    m_textureReferenceCounts.push_back(0);
    m_textureClasses.push_back(Texture(filepath));
    return m_textureClasses.size()-1;
}

uint32_t AssetSystem::GetTextureIdFromPath(const std::string& filepath) {
    for(uint32_t i = 0; i < m_textureClasses.size(); i++) {
        if(m_textureClasses[i].HasFilepath(filepath))
            return i;
    }
    return 0xFFFFFFFF;
}

std::shared_ptr<TextureReference> AssetSystem::LoadTexture(uint32_t textureId) {
    if(m_textureReferenceCounts[textureId]<=0)
        m_textureLoadStack.push_back(textureId);
    m_textureReferenceCounts[textureId]++;
    return std::make_shared<TextureReference>(this, textureId);
}

std::shared_ptr<TextureReference> AssetSystem::NullTexture() {
    return std::make_shared<TextureReference>(this, 0); //In constructor
}

void AssetSystem::OnTextureReferenceRemoved(uint32_t textureId) {
    m_textureReferenceCounts[textureId]--;
    if(m_textureReferenceCounts[textureId]<=0) {
        m_textureUnloadStack.push_back(textureId);
    }
}

void AssetSystem::DoAllLoading() {
    //Meshes
    while(m_meshUnloadStack.size() > 0) {
        std::cout << "Unloading mesh " << m_meshUnloadStack.back() << std::endl;
        m_meshClasses[m_meshUnloadStack.back()].UnloadMesh();
        m_meshUnloadStack.pop_back();
    }
    while(m_meshLoadStack.size() > 0) {
        std::cout << "Loading mesh " << m_meshLoadStack.back() << std::endl;
        m_meshClasses[m_meshLoadStack.back()].LoadMesh();
        m_meshLoadStack.pop_back();
    }
    //Textures
    while(m_textureUnloadStack.size() > 0) {
        std::cout << "Unloading texture " << m_textureUnloadStack.back() << std::endl;
        m_textureClasses[m_textureUnloadStack.back()].UnloadTexture();
        m_textureUnloadStack.pop_back();
    }
    while(m_textureLoadStack.size() > 0) {
        std::cout << "Loading texture " << m_textureLoadStack.back() << std::endl;
        m_textureClasses[m_textureLoadStack.back()].LoadTexture();
        m_textureLoadStack.pop_back();
    }
}
