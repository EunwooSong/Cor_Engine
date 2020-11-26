#include "stdafx.h"
#include "EntityIDManager.h"

EntityIDManager::EntityIDManager()
{
	for (EntityID entity = 0; entity < MAX_ENTITIES; ++entity)
	{
		m_AvailableEntityIDs.push(entity);
	}
}

EntityID EntityIDManager::CreateEntityID()
{
	assert(m_LivingEntityIDCount < MAX_ENTITIES && "Entity out of range.");

	EntityID id = m_AvailableEntityIDs.front();
	m_AvailableEntityIDs.pop();
	++m_LivingEntityIDCount;

	return id;
}

void EntityIDManager::DestroyEntityID(EntityID _id)
{
	assert(_id < MAX_ENTITIES && "Entity out of range.");
	m_Signatures[_id].reset();

	m_AvailableEntityIDs.push(_id);
	--m_LivingEntityIDCount;
}

void EntityIDManager::SetSignature(EntityID _id, Signature signature)
{
	assert(_id < MAX_ENTITIES && "Entity out of range.");

	m_Signatures[_id] = signature;
}

Signature EntityIDManager::GetSignature(EntityID _id)
{
	assert(_id < MAX_ENTITIES && "Entity out of range.");

	return m_Signatures[_id];
}
