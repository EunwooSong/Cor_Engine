#pragma once

#include "ECS_Type.h"
#include "Component.h"
#include <iostream>
#include <array>
#include <cassert>
#include <unordered_map>

class IComponentArray {
public:
    virtual ~IComponentArray() = default;
    virtual void EntityDestroyed(EntityID _id) = 0;
    virtual std::vector<Component*> GetComponentArray() = 0;
};

template<typename T>
class ComponentArray : public IComponentArray {
public:
    ~ComponentArray() {
        /*int i = 0;
        for (auto& iter : m_ComponentArray) {
            i++;
            if (iter) SAFE_DELETE(dynamic_cast<Component*>(iter));
        }*/
    }

    void AddComponent(EntityID _id, T* component) {
        assert(m_EntityToIndexMap.find(_id) == m_EntityToIndexMap.end() && "Component added to same entity more than once.");

        // Put new entry at end and update the maps
        size_t newIndex = m_Size;
        m_EntityToIndexMap[_id] = newIndex;
        m_IndexToEntityMap[newIndex] = _id;
        m_ComponentArray.push_back(component);

        m_Size++;
    }

    void DestroyComponent(EntityID _id) {
        assert(m_EntityToIndexMap.find(_id) != m_EntityToIndexMap.end() && "Removing non-existent component");

        size_t indexOfRemovedEntity = m_EntityToIndexMap[_id];
        size_t indexOfLastElement = m_Size - 1;
        SAFE_DELETE(
            m_ComponentArray[indexOfRemovedEntity]);
        m_ComponentArray[indexOfRemovedEntity] = m_ComponentArray[indexOfLastElement];
        m_ComponentArray.erase(m_ComponentArray.begin() + indexOfLastElement);

        EntityID entityOfLastElement = m_IndexToEntityMap[indexOfLastElement];
        m_EntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
        m_IndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

        m_EntityToIndexMap.erase(_id);
        m_IndexToEntityMap.erase(indexOfLastElement);

        --m_Size;
    }

    T* GetComponent(EntityID _id) {
        assert(m_EntityToIndexMap.find(_id) != m_EntityToIndexMap.end() && "Retrieving non-existent component");
        if (m_EntityToIndexMap.find(_id) == m_EntityToIndexMap.end()) {
            std::cout << "Retrieving non-existent component" << std::endl;
            return nullptr;
        }

        return m_ComponentArray[m_EntityToIndexMap[_id]];
    }

    void EntityDestroyed(EntityID _id) override {
        if (m_EntityToIndexMap.find(_id) != m_EntityToIndexMap.end()) {
            // Remove the entity's component if it existed
            DestroyComponent(_id);
        }
    }

    std::vector<Component*> GetComponentArray() override {
        std::vector<Component*> m_compoArray{};
        for (auto iter : m_ComponentArray)
            m_compoArray.push_back(dynamic_cast<Component*>(iter));

        return m_compoArray;
    }

private:
    std::vector<T*> m_ComponentArray;
    std::unordered_map<EntityID, size_t> m_EntityToIndexMap;
    std::unordered_map<size_t, EntityID> m_IndexToEntityMap;

    // Total size of valid entries in the array.
    size_t m_Size;
};

