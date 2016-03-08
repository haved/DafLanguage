#include "Scene.h"

Scene::Scene(){
    root.SetSceneRecursivly(this);
}

void Scene::AddObject(std::shared_ptr<GameObject> object) {
    root.AddChild(object);
}

void Scene::Update() {
    root.Update();
}

void Scene::Render(const glm::mat4 &VP) {
    root.Render(VP);
}
