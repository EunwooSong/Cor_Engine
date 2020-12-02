#include "stdafx.h"
#include "Scene.h"
#include "AnimationController.h"
#include "Transform.h"
#include "RigidBody2D.h"
#include "BoxCollider.h"
#include "Sprite2DRenderer.h"
#include "Button.h"
#include "GameObject.h"
#include "CLogger.h"

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
    RegisterComponent<AnimationController>();
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

GameObject* Scene::FindGameObject(std::string name)
{
    for (auto iter : m_EntityList) {
        if (iter.second->GetName().compare(name) == 0)
            return dynamic_cast<GameObject*>(iter.second);
    }

    CLogger::Error("Failed to find game object name : %s ", name.c_str());
    return nullptr;
}