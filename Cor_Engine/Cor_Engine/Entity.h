#pragma once

#include "ECS_Type.h"

class Component;
class Scene;

class Entity {
public:
    Entity();
    ~Entity() {}

    virtual void Init() = 0;

    void SetTag(std::string tag) { this->tag = tag; }
    std::string GetTagI() { return tag; }
    bool GetIsDestroy() { return isDestroy; }
    bool GetIsActive() { return isActive; };
    void SetIsActive(bool isActive);

    Scene* GetScene() { return m_Scene; }
    EntityID GetEntityID() { return m_id; };

    static void Destroy(Entity* iter) { iter->SetIsDestroy(true); }

protected:
    void SetIsDestroy(bool isDestroy) { this->isDestroy = isDestroy; }

    EntityID m_id;
    std::string tag;
    Scene* m_Scene;
    std::vector<Component*> m_components;
    bool isDestroy;
    bool isActive;
};