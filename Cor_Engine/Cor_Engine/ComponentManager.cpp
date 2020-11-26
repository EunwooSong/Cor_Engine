#include "stdafx.h"
#include "Component.h"
#include "GameObject.h"
#include "ComponentManager.h"

void ComponentManager::Start()
{
    for (auto const& pair : m_ComponentArrays) {
        auto const& components = pair.second;

        for (auto compoIter : components->GetComponentArray()) {
            if (compoIter)
                if (!compoIter->GetIsStarted())
                    compoIter->Start();
        }
    }
}
void ComponentManager::Update() {
    for (auto const& pair : m_ComponentArrays) {
        auto const& components = pair.second;

        auto const& componentArray = components->GetComponentArray();

        for (auto compoIter : componentArray) {
            if (compoIter)
                compoIter->Update();
        }
    }
}
void ComponentManager::LateUpdate() {
    for (auto const& pair : m_ComponentArrays) {
        auto const& components = pair.second;

        auto const& componentArray = components->GetComponentArray();

        for (auto compoIter : componentArray) {
            if (compoIter)
                compoIter->LateUpdate();
        }
    }
}
void ComponentManager::Render() {
    for (auto const& pair : m_ComponentArrays) {
        auto const& components = pair.second;

        auto const& componentArray = components->GetComponentArray();

        for (auto compoIter : componentArray) {
            if (compoIter)
                compoIter->Render();
        }
    }
}
void ComponentManager::EndScene() {
    for (auto const& pair : m_ComponentArrays) {
        auto const& components = pair.second;

        auto const& componentArray = components->GetComponentArray();

        for (auto compoIter : componentArray) {
            if (compoIter)
                compoIter->EndScene();
        }
    }
}
ComponentManager::~ComponentManager() {
    for (auto const& pair : m_ComponentArrays) {
        auto const& components = pair.second;

        auto const& componentArray = components->GetComponentArray();

        for (auto compoIter : componentArray) {
            if(compoIter) SAFE_DELETE(compoIter);
        }
    }
}
std::vector<Component*> ComponentManager::FindEntityComponents(EntityID _id) {
    std::vector<Component*> compos;

    for (auto const& pair : m_ComponentArrays) {
        auto const& components = pair.second;

        auto const& componentArray = components->GetComponentArray();

        for (Component* compoIter : componentArray) {
            if (compoIter->GetOwner()->GetEntityID() == _id) {
                compos.push_back(compoIter);
                continue;
            }
        }
    }

    return compos;
}