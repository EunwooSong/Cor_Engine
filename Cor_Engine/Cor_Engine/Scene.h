#pragma once
#include "ECS_Type.h"
#include <list>
#include <map>
#include <vector>
#include "Entity.h"
#include "EntityIDManager.h"
#include "ComponentManager.h"

class Scene {
public:
    Scene();
    ~Scene();

    //Hierarchy, Initialize gameObject
    //Ex, Player* player = new Player();
    virtual void Init() = 0;
    void Start();
    void Update();
    void LateUpdate();
    void Render();
    void EndScene();

    EntityID CreateEntity(Entity* iter) {
        EntityID tmp = m_EntityIDManager->CreateEntityID();
        m_EntityList.insert(std::pair<EntityID, Entity*>(tmp, iter));
        iter->Init();
        return tmp;
    }

    void DestroyEntity(EntityID _id) {
        m_EntityIDManager->DestroyEntityID(_id);
        m_ComponentManager->EntityDestroyed(_id);

        SAFE_DELETE(m_EntityList[_id]);
        m_EntityList.erase(_id);
    }

    template <typename T>
    void RegisterComponent() {
        m_ComponentManager->RegisterComponent<T>();
    }

    template <typename T>
    void DestroyComponent(EntityID _id) {
        m_ComponentManager->DestroyComponent<T>(_id);

        auto signature = m_EntityIDManager->GetSignature(_id);
        signature.set(m_ComponentManager->GetComponentID<T>(), false);
    }

    template <typename T>
    void AddComponent(Entity* _id, T* iter) {
        m_ComponentManager->AddComponent<T>(_id->GetEntityID(), iter);
        dynamic_cast<Component*>(iter)->SetOwner(_id);
        auto signature = m_EntityIDManager->GetSignature(_id->GetEntityID());
        signature.set(m_ComponentManager->GetComponentID<T>(), true);
        m_EntityIDManager->SetSignature(_id->GetEntityID(), signature);
    };

    template <typename T>
    T* GetComponent(EntityID _id) {
        return m_ComponentManager->GetComponent<T>(_id);
    }

    template <typename T>
    ComponentID GetComponentType() {
        return m_ComponentManager->GetComponentID<T>();
    }

    template <typename T>
    std::vector<T*> GetComponentArray() {
        return m_ComponentManager->GetTypeComponentList<T>();
    }

    void RegisterCollider(BoxCollider* a, BoxCollider* b) {
        m_ColliderManager->MountCollider(a, b);
    }

    std::vector<Component*> FindEntityComponents(EntityID _id);

    std::map<EntityID, Entity*> m_EntityList;

private:
    std::unique_ptr<ComponentManager> m_ComponentManager;
    std::unique_ptr<EntityIDManager> m_EntityIDManager;
    std::unique_ptr<ColliderManager> m_ColliderManager;
    //        std::unique_ptr
};