#include "stdafx.h"
#include "UnitMovement.h"
#include "ZeroSystem.h"
#include "GameObject.h"
#include "Transform.h"
#include "ZeroSystem.h"
#include "CLogger.h"

void UnitMovement::Start()
{
	Component::Start();

	_anim		= GetOwner()->GetComponent<AnimationController>();
	renderer	= GetOwner()->GetComponent<Sprite2DRenderer>();
	tr			= GetOwner()->GetComponent<Transform>();
	rigid		= GetOwner()->GetComponent<RigidBody2D>();

	if (team == Team::TEAM_2)
		tr->SetScale(-tr->GetScale().x, tr->GetScale().y);
}

void UnitMovement::Update()
{
	Component::Update();

	Vec2 moveDir = Vec2(1.0f, 0.0f);

	if (team == Team::TEAM_2)
		moveDir.x = -1.0f;

	//Check Forward Object
	Vec2 current = tr->GetWorldPos();

	if (team == Team::TEAM_1) {
		float checkX = current.x + stopRange;

		if (myIter - 1 != teamMgr->team1_unit.begin()) {
			Transform* tmpTr = (*(myIter - 1))->transform;
			Vec2 tmpP = tmpTr->GetWorldPos();
			
			if (checkX > tmpP.x)
				isMove = false;
			else
				isMove = true;

			if ((*(myIter - 1))->GetComponent<UnitMovement>()->GetType() == UnitType::MONKS)
				if (!isMove)
					isMove = true;
		}

		checkX = current.x + attackRange;
		for (auto tmp : teamMgr->team2_unit) {
			if (checkX > tmp->transform->GetWorldPos().x && current.x < tmp->transform->GetWorldPos().x) {
				isMove = false;
				isAttack = true;
				break;
			}
			else {
				isAttack = false;
			}
		}
	}
	else {
		float checkX = current.x - stopRange;

		if (myIter - 1 != teamMgr->team2_unit.begin()) {
			Transform* tmpTr = (*(myIter - 1))->transform;
			Vec2 tmpP = tmpTr->GetWorldPos();
			if (checkX < tmpP.x)
				isMove = false;
			else
				isMove = true;

			if ((*(myIter - 1))->GetComponent<UnitMovement>()->GetType() == UnitType::MONKS)
				if (!isMove)
					isMove = true;
		}

		checkX = current.x + attackRange;
		for (auto tmp : teamMgr->team2_unit) {
			if (checkX > tmp->transform->GetWorldPos().x && current.x < tmp->transform->GetWorldPos().x) {
				isMove = false;
				isAttack = true;
				break;
			}
			else {
				isAttack = false;
			}
		}
	}

	if (isMove)
		rigid->AddVelocity(moveDir * moveSpeed * ZERO_TIME_MGR->GetDeltaTime());

	if (isAttack) {
		attackTimer += ZERO_TIME_MGR->GetDeltaTime();

		if (attackTimer > attackDelay) {
			Attack();
			CLogger::Debug("Attack! %d", GetOwner()->GetEntityID());
		}
	}
}

void UnitMovement::Attack()
{
	//Ÿ�Կ� ���� �����ϴ� Object�ٸ�
}

void UnitMovement::InitType(Team team, UnitType type)
{
	this->team = team;
	this->type = type;
}