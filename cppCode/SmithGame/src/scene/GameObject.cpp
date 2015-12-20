#include "GameObject.h"
#include "Scene.h"
#include <algorithm>

GameObject::GameObject() {
    parent=NULL;
    scene=NULL;
}

void GameObject::SetScene(Scene* scene) {
    this->scene = scene;
    for(GameObject &child:children) {
        child.SetScene(scene);
    }
    for(std::shared_ptr<GameComponent> &cmp:components) {
        cmp->OnSceneSet(scene);
    }
}

void GameObject::SetParent(GameObject* parent) {
    this->parent = parent;
}

void GameObject::AddChild(GameObject &child) {
    this->children.push_back(child);
    child.SetParent(this);
    child.SetScene(scene);
}

void GameObject::AddComponent(std::shared_ptr<GameComponent> component) {
    this->components.push_back(component);
    component->SetParent(this);
    component->OnSceneSet(scene);
}

void GameObject::Update() {
    for(unsigned int i = 0; i < components.size(); i++) {
        components[i]->Update();
    }
    for(unsigned int i = 0; i < children.size(); i++) {
        children[i].Update();
    }
}

void GameObject::Render(glm::mat4 &VP) {
    for(unsigned int i = 0; i < components.size(); i++) {
        components[i]->Render(VP);
    }
    for(unsigned int i = 0; i < children.size(); i++) {
        children[i].Render(VP);
    }
}
