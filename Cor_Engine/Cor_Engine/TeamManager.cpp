#include "stdafx.h"
#include "TeamManager.h"
#include "GameObject.h"
#include "ZeroSystem.h"
#include "UnitBaseObject.h"
#include "UnitMovement.h"

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

	if (ZERO_INPUT_MGR->GetKeyState('1') == KEY_DOWN) {
		UnitBaseObject* obj = new UnitBaseObject();
		obj->GetComponent<UnitMovement>()->InitType(Team::TEAM_1, UnitType::SWORD);
		team1_unit.push_back(obj);
		obj->GetComponent<UnitMovement>()->myIter = team1_unit.begin() + (team1_unit.size() - 1);
		CLogger::Info("id : %d", (*obj->GetComponent<UnitMovement>()->myIter)->GetEntityID());
	}
}

void TeamManager::LateUpdate()
{
	Component::LateUpdate();
	CheckDeathUnit();
}

void TeamManager::CheckDeathUnit()
{
}
