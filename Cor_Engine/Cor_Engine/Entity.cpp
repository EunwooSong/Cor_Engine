#include "stdafx.h"
#include "Entity.h"
#include "Component.h"
#include "ZeroSystem.h"
#include "GameObject.h"

Entity::Entity() : m_id(-1), m_Scene(nullptr), isDestroy(false), isActive(true)
{
	m_Scene = ZERO_ENGINE->GetSceneManager()->GetCurrentScene();
	m_id = m_Scene->CreateEntity(this);
}

void Entity::SetIsActive(bool isActive)
{
	this->isActive = isActive;

	for (auto iter : m_components) {
		iter->SetActive(isActive);
	}
}
