#pragma once

#include <glm/glm.hpp>

class Scene;
class GameObject;

class GameComponent
{
    public:
        virtual void OnSceneSet(Scene* scene);
        inline void SetParent(GameObject* parent) {
            this->parent = parent;
        }
        virtual void Update()=0;
        virtual void Render(glm::mat4 &VP)=0;
    protected:
        GameObject* parent;
    private:
};
