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

		for (auto tmp : teamMgr->team1_unit) {
			if (tmp == GetOwner()) break;

			Transform* tmpTr = tmp->transform;
			Vec2 tmpP = tmpTr->GetWorldPos();

			if (checkX > tmpP.x)
				isMove = false;
			else
				isMove = true;

			if (tmp->GetComponent<UnitMovement>()->GetType() == UnitType::MONKS)
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
	else if(team == Team::TEAM_2){
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
		tr->Translate(moveDir * moveSpeed * ZERO_TIME_MGR->GetDeltaTime());
	/*else
		CLogger::Error("WTF?");*/
	if (isAttack) {
		attackTimer += ZERO_TIME_MGR->GetDeltaTime();

		if (attackTimer > attackDelay) {
			Attack();
			CLogger::Debug("Attack! %d", GetOwner()->GetEntityID());
			attackTimer = 0.0f;
		}
	}
}

void UnitMovement::Attack()
{
	//타입에 따라 생성하는 Object다름
}

void UnitMovement::InitType(Team team, UnitType type)
{
	this->team = team;
	this->type = type;

	_anim = GetOwner()->GetComponent<AnimationController>();
	renderer = GetOwner()->GetComponent<Sprite2DRenderer>();
	tr = GetOwner()->GetComponent<Transform>();
	rigid = GetOwner()->GetComponent<RigidBody2D>();

	if (team == Team::TEAM_2)
		tr->SetScale(-tr->GetScale().x, tr->GetScale().y);

	teamMgr = GetOwner()->GetScene()->FindGameObject("TeamMgr")->GetComponent<TeamManager>();


	SpriteAnimation* anim_move = new SpriteAnimation();
	SpriteAnimation* anim_attack = new SpriteAnimation();

	//Animation등록
	switch (type)
	{
	case UnitType::NONE:
		break;

	case UnitType::SWORD:
		anim_move->SetFps(2);
		anim_move->AddTextures("Resources/Character/칼병/Walk", 2);

		anim_attack->SetFps(2);
		anim_attack->AddTextures("Resources/Character/칼병/Attack", 2);

		renderer->SetTexture("Resources/Character/칼병/Walk/1.png");
		break;

	case UnitType::BOW:
		anim_move->SetFps(2);
		anim_move->AddTextures("Resources/Character/활병/Walk", 2);

		anim_attack->SetFps(3);
		anim_attack->AddTextures("Resources/Character/활병/Attack", 3);

		renderer->SetTexture("Resources/Character/활병/Walk/1.png");
		break;
	case UnitType::SHIELD:
		break;
	case UnitType::SLAVE:
		break;
	case UnitType::MONKS:
		break;
	case UnitType::BUTCHRE:
		break;
	case UnitType::CLOWN:
		break;
	case UnitType::GISAENG:
		break;
	default:
		break;
	}

	_anim->AddAnimationNode("Move", anim_move);
	_anim->AddAnimationNode("Attack", anim_attack);
	_anim->SetEntryAnimationNode("Move");
}