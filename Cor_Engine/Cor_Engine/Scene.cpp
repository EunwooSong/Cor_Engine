#include "stdafx.h"
#include "Scene.h"


Scene::Scene() {
}
Scene::~Scene() {
    //Reset Signature
    for (auto iter : m_EntityList) {
        SAFE_DELETE(iter.second);
    }
}
void Scene::Init() {
    m_ComponentManager = std::make_unique<ComponentManager>();
    m_EntityIDManager = std::make_unique<EntityIDManager>();
    m_ColliderManager = std::make_unique<ColliderManager>();

    //Register Component(Transform, RigidBody, 2D Renderer, Collider . . .)
    RegisterComponent<Transform>();
    RegisterComponent<CameraComponent>();
    RegisterComponent<RigidBody2D>();
    RegisterComponent<Sprite2DRenderer>();
    RegisterComponent<BoxCollider>();
    RegisterComponent<Button>();
}
void Scene::Start() {
    m_ComponentManager->Start();
}
void Scene::Update() {
    m_ComponentManager->Update();
    m_ColliderManager->Update();
}
void Scene::LateUpdate() {
    m_ComponentManager->LateUpdate();
    m_ColliderManager->LateUpdate();
}
void Scene::Render() {
    m_ComponentManager->Render();
}
void Scene::EndScene() {
    //Destroy Entity Objects
    m_ComponentManager->EndScene();

    for (auto iter = m_EntityList.begin(); iter != m_EntityList.end(); ++iter) {
        if (iter->second->GetIsDestroy()) {
            auto tmp = iter++;
            DestroyEntity(tmp->first);

            if (iter == m_EntityList.end())
                break;
        }
    }
}

std::vector<Component*> Scene::FindEntityComponents(EntityID _id) {
    return m_ComponentManager->FindEntityComponents(_id);
}