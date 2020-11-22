#pragma once
#include "Entity.h"
#include "Component.h"
#include "Scene.h"

class Transform;

class GameObject :
    public Entity
{
public:
    GameObject() : transform(nullptr) {}
    ~GameObject() {}

    virtual void Init() override;

    template<typename T>
    T* AddComponent() {
        T* compo = new T();
        m_Scene->AddComponent<T>(this, compo);
        m_components.push_back(dynamic_cast<Component*>(compo));

        return compo;
    }

    template<typename T>
    T* GetComponent() {
        return m_Scene->GetComponent<T>(GetEntityID());
    }

    Transform* transform;
};

