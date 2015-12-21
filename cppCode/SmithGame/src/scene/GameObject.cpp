#include "GameObject.h"
#include "Scene.h"
#include <algorithm>
#define GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>

void GameObject::SetSceneRecursivly(Scene* scene) {
    if(this->scene != NULL)
        for(std::shared_ptr<GameComponent> &cmp:components) {
            cmp->BeforeRemovedFromScene(this->scene);
        }
    this->scene = scene;
    for(std::shared_ptr<GameObject> &child:children) {
        child->SetSceneRecursivly(scene);
    }
    if(scene!=NULL) {
        for(std::shared_ptr<GameComponent> &cmp:components) {
            cmp->OnAddedToScene(scene);
        }
    }
}

void GameObject::SetParent(GameObject* parent) {
    this->parent = parent;
}

void GameObject::AddChild(std::shared_ptr<GameObject> child) {
    this->children.push_back(child);
    child->SetParent(this);
    child->SetSceneRecursivly(scene);
}

void GameObject::AddComponent(std::shared_ptr<GameComponent> component) {
    this->components.push_back(component);
    component->SetParent(this);
    if(scene!=NULL)
        component->OnAddedToScene(scene);
}

void GameObject::Update() {
    for(unsigned int i = 0; i < components.size(); i++) {
        components[i]->Update();
    }
    for(unsigned int i = 0; i < children.size(); i++) {
        children[i]->Update();
    }
}

void GameObject::Render(const glm::mat4 &VP) {
    if(localChanged) {
        localModelspace = glm::translate(pos) * glm::rotate(rot.z, glm::vec3(0,0,1)) * glm::rotate(rot.x, glm::vec3(1,0,0)) * glm::rotate(rot.y, glm::vec3(0,1,0)) * glm::scale(scale);
        localChanged = false;
        globalChanged = true;
    }

    if(globalChanged) {
        if(parent==NULL)
            globalModelspace = localModelspace;
        else
            globalModelspace = parent->globalModelspace * localModelspace;

        for(unsigned int i = 0; i < children.size(); i++)
            children[i]->globalChanged = true;
        globalChanged = false;
    }

    if(renderSelf) {
        glm::mat4 MVP = VP*globalModelspace;
        for(unsigned int i = 0; i < components.size(); i++) {
            components[i]->Render(MVP);
        }
    }
    for(unsigned int i = 0; i < children.size(); i++) {
        children[i]->Render(VP);
    }
}
