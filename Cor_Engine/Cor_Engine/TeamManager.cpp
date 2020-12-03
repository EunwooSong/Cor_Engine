#include "stdafx.h"
#include "TeamManager.h"
#include "GameObject.h"

TeamManager::TeamManager()
{
}

TeamManager::~TeamManager()
{
}

void TeamManager::Start()
{
	Component::Start();
}

void TeamManager::Update()
{
	Component::Update();
}

void TeamManager::LateUpdate()
{
	Component::LateUpdate();
	CheckDeathUnit();
}

void TeamManager::CheckDeathUnit()
{
}
