#pragma once
#include "ECS_Type.h"

#include <array>
#include <cassert>
#include <queue>

class EntityIDManager {
public:
    EntityIDManager();
    ~EntityIDManager() {};

    EntityID CreateEntityID();
    void DestroyEntityID(EntityID _id); 

    void SetSignature(EntityID _id, Signature signature);

    Signature GetSignature(EntityID _id);

private:
    std::queue<EntityID> m_AvailableEntityIDs{};
    std::array<Signature, MAX_ENTITIES> m_Signatures{};
    uint32_t m_LivingEntityIDCount{};
};