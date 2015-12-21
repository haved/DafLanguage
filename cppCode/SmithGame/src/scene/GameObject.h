#pragma once

#include <vector>
#include <memory>
#include "GameComponent.h"
#include <glm/glm.hpp>

class Scene;

class GameObject {
public:
    void SetSceneRecursivly(Scene* scene);
    void SetParent(GameObject* object);
    void AddChild(std::shared_ptr<GameObject> child);
    void AddComponent(std::shared_ptr<GameComponent> component);
    void Update();
    void Render(const glm::mat4 &VP);
    inline const glm::vec3* GetPosPointer() {
        return &pos;
    }
    inline const glm::vec3* GetRotPointer() {
        return &rot;
    }
    inline const glm::vec3* GetScalePointer() {
        return &scale;
    }
    inline glm::vec3 GetPos() {
        return pos;
    }
    inline glm::vec3 GetRot() {
        return rot;
    }
    inline glm::vec3 GetScale() {
        return scale;
    }
    inline void SetPos(const glm::vec3 &pos) {
        this->pos = pos;
        localChanged = true;
    }
    inline void SetRot(const glm::vec3 &rot) {
        this->rot = rot;
        localChanged = true;
    }
    inline void SetScale(const glm::vec3 &scale) {
        this->scale = scale;
        localChanged = true;
    }
    inline glm::vec3* GetMutPosPointer() {
        localChanged = true;
        return &pos;
    }
    inline glm::vec3* GetMutRotPointer() {
        localChanged = true;
        return &rot;
    }
    inline glm::vec3* GetMutScalePointer() {
        localChanged = true;
        return &scale;
    }
    inline void SetToRenderSelf() {
        renderSelf = true;
    }
private:
    std::vector<std::shared_ptr<GameObject>> children {};
    std::vector<std::shared_ptr<GameComponent>> components {};
    GameObject* parent=NULL;
    Scene* scene=NULL;
    bool renderSelf=false;
    glm::vec3 pos=glm::vec3(0,0,0);
    glm::vec3 rot=glm::vec3(0,0,0);
    glm::vec3 scale=glm::vec3(1,1,1);
    glm::mat4 localModelspace=glm::mat4(1.f);
    glm::mat4 globalModelspace=glm::mat4(1.f);
    bool localChanged=false;
    bool globalChanged=false;
};
