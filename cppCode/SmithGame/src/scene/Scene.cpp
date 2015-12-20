#include "Scene.h"

void Scene::AddObject(GameObject& object) {
    root.AddChild(object);
    object.SetScene(this);
}

void Scene::Update() {
    root.Update();
}

void Scene::Render(glm::mat4 &VP) {
    root.Render(VP);
}
