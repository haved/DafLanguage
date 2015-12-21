#pragma once

#include <glm/glm.hpp>

class Scene;
class GameObject;

class GameComponent
{
    public:
        virtual void SetParent(GameObject* parent){};
        virtual void OnAddedToScene(Scene* parent){};
        virtual void BeforeRemovedFromScene(Scene* parent){};
        virtual void Update()=0;
        virtual void Render(const glm::mat4 &MVP)=0;
    protected:
        GameObject* parent=NULL;
    private:
};
