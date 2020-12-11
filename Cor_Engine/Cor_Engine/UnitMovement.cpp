#include "stdafx.h"
#include "UnitMovement.h"
#include "ZeroSystem.h"
#include "GameObject.h"
#include "Transform.h"
#include "ZeroSystem.h"
#include "CLogger.h"
#include "ZeroMath.h"
#include "UIHp.h"

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
		float checkX = 0.0f;

		/*checkX = current.x + stopRange;
		if (GetType() < UnitType::SHIELD) {
			for (auto tmp : teamMgr->team1_unit) {
				if (tmp == GetOwner()) break;

				Transform* tmpTr = tmp->transform;
				Vec2 tmpP = tmpTr->GetWorldPos();

				UnitMovement* movement = tmp->GetComponent<UnitMovement>();
				if (movement->GetType() > UnitType::SHIELD)
					continue;

				if (checkX > tmpP.x)
					isMove = false;
				else
					isMove = true;

				if (tmp->GetComponent<UnitMovement>()->GetType() == UnitType::MONKS)
					if (!isMove)
						isMove = true;
			}
		}*/
		checkX = current.x + attackRange;

		//if (GetType() != UnitType::MONKS) {
			for (auto tmp : teamMgr->team2_unit) {
				if (checkX > tmp->transform->GetWorldPos().x && current.x < tmp->transform->GetWorldPos().x) {
					isMove = false;
					isAttack = true;

					//승려가 노비의 어그로에 끌림
					if (GetType() == UnitType::MONKS) {
						if (tmp->GetComponent<UnitMovement>()->GetType() == UnitType::SLAVE) {
							isMove = false;
							isAttack = true;
							break;
						}
						else {
							isMove = true;
							isAttack = false;
						}
					}
					else
						break;
					//---------------------------------------------------------
				}
				else {
					isMove = true;
					isAttack = false;
				}
			}
			if (teamMgr->team2_unit.empty()) {
				isAttack = false;
				isMove = true;
			}
		//}

		if (checkX > teamMgr->teamBase2->transform->GetLocalPos().x) {
			isAttack = true;
			isMove = false;
		}
	}
	else if(team == Team::TEAM_2){
		float checkX = 0.0f;

		/*checkX = current.x - stopRange;
		if (GetType() < UnitType::SHIELD) {
			for (auto tmp : teamMgr->team2_unit) {
				if (tmp == GetOwner()) break;

				Transform* tmpTr = tmp->transform;
				Vec2 tmpP = tmpTr->GetWorldPos();

				UnitMovement* movement = tmp->GetComponent<UnitMovement>();
				if (movement->GetType() > UnitType::SHIELD)
					continue;

				if (checkX < tmpP.x)
					isMove = false;
				else
					isMove = true;

				if (tmp->GetComponent<UnitMovement>()->GetType() == UnitType::MONKS)
					if (!isMove)
						isMove = true;
			}
		}*/

		checkX = current.x - attackRange;
		//if (GetType() != UnitType::MONKS) {
			for (auto tmp : teamMgr->team1_unit) {
				if (checkX < tmp->transform->GetWorldPos().x && current.x > tmp->transform->GetWorldPos().x) {
					isMove = false;
					isAttack = true;

					//승려가 노비의 어그로에 끌림
					if (GetType() == UnitType::MONKS) {
						if (tmp->GetComponent<UnitMovement>()->GetType() == UnitType::SLAVE) {
							isMove = false;
							isAttack = true;
							break;
						}
						else {
							isMove = true;
							isAttack = false;
						}
					}
					else
						break;
					//---------------------------------------------------------
				}
				else {
					isMove = true;
					isAttack = false;
				}
			}
			if (teamMgr->team1_unit.empty()) {
				isAttack = false;
				isMove = true;
			}
		//}
		if (checkX < teamMgr->teamBase1->transform->GetLocalPos().x) {
			isAttack = true;
			isMove = false;
		}


		if (ZERO_INPUT_MGR->GetKeyState('R') == KEY_DOWN)
			hp = 0.0f;
	}

	if (isMove)
		tr->Translate(moveDir * moveSpeed * ZERO_TIME_MGR->GetDeltaTime());

	if (type == UnitType::GISAENG) {
		attackTimer += ZERO_TIME_MGR->GetDeltaTime();

		if (attackTimer > attackCurrentDelay) {
			Attack();
			attackTimer = 0.0f;
		}
	}
	else if(type == UnitType::CLOWN) {
		Attack();
	}
	else {
		if (isAttack) {
			attackTimer += ZERO_TIME_MGR->GetDeltaTime();

			if (attackTimer > attackCurrentDelay) {
				Attack();
				attackTimer = 0.0f;
			}
		}
	}
	

	_anim->SetBool("IsWalk", isMove);
	_anim->SetBool("IsAttack", isAttack);
}

void UnitMovement::LateUpdate()
{
	Component::LateUpdate();

	bar->SetVisibleRect(Rect(65 * hp / maxHp, 13));
}

void UnitMovement::Attack()
{
	//타입에 따라 행동하는 것이 다름
	UnitType type = GetType();
	Vec2 currentPos = tr->GetLocalPos();
	float checkX = currentPos.x + attackRange * tr->GetScale().x;
	
	float min = 2.0f;

	switch (type)
	{
	case UnitType::NONE:
		break;
	case UnitType::SWORD:
	case UnitType::SLAVE:
	case UnitType::BUTCHRE:
		if (team == Team::TEAM_1) {
			for (auto tmp : teamMgr->team2_unit) {
				if (checkX > tmp->transform->GetWorldPos().x && currentPos.x < tmp->transform->GetWorldPos().x) {
					UnitMovement* target = tmp->GetComponent<UnitMovement>();

					if (attackTarget == nullptr) {
						attackTarget = target;
					}
					else if (target->type == UnitType::SLAVE) {
						attackTarget = target;
						break;
					}
				}
			}
		}
		else if (team == Team::TEAM_2) {
			for (auto tmp : teamMgr->team1_unit) {
				if (checkX < tmp->transform->GetWorldPos().x && currentPos.x > tmp->transform->GetWorldPos().x) {
					UnitMovement* target = tmp->GetComponent<UnitMovement>();

					if (attackTarget == nullptr) {
						attackTarget = target;
					}
					else if (target->type == UnitType::SLAVE) {
						attackTarget = target;
						break;
					}
				}
			}
		}

		//유닛 or 기지 공격
		if(attackTarget != nullptr)
			attackTarget->GetDamage(attackPower);
		else
			if (team == Team::TEAM_1) {
				if (checkX > teamMgr->teamBase2->transform->GetLocalPos().x) {
					teamMgr->baseHp_2 -= attackPower;
				}
			}
			else if (team == Team::TEAM_2) {
				if (checkX < teamMgr->teamBase1->transform->GetLocalPos().x) {
					teamMgr->baseHp_1 -= attackPower;
				}
			}

		// 특수 유닛 처리
		if (type == UnitType::BUTCHRE)
			if (hp + 30 < maxHp)
				hp += 30;
			else
				hp = maxHp;

		attackTarget = nullptr;
		break;
		
	case UnitType::BOW:
		teamMgr->CreateBullet(team, attackPower, tr->GetLocalPos() + Vec2(0.0f, 20));
		break;

	case UnitType::MONKS:
		if (team == Team::TEAM_1) {
			for (auto tmp : teamMgr->team2_unit) {
				if (checkX > tmp->transform->GetWorldPos().x && currentPos.x < tmp->transform->GetWorldPos().x) {
					UnitMovement* target = tmp->GetComponent<UnitMovement>();

					if (target->GetType() == UnitType::SLAVE) {
						attackTarget = target;
						break;
					}
				}
			}
		}
		else if (team == Team::TEAM_2) {
			for (auto tmp : teamMgr->team1_unit) {
				if (checkX < tmp->transform->GetWorldPos().x && currentPos.x > tmp->transform->GetWorldPos().x) {
					UnitMovement* target = tmp->GetComponent<UnitMovement>();

					if (target->GetType() == UnitType::SLAVE) {
						attackTarget = target;
						break;
					}
				}
			}
		}

		if (!attackTarget) {
			if (team == Team::TEAM_1) {
				if (checkX > teamMgr->teamBase2->transform->GetLocalPos().x) {
					teamMgr->baseHp_2 -= attackPower;
				}
			}
			else if (team == Team::TEAM_2) {
				if (checkX < teamMgr->teamBase1->transform->GetLocalPos().x) {
					teamMgr->baseHp_1 -= attackPower;
				}
			}
		}

		else
			attackTarget->GetDamage(attackPower);

		attackTarget = nullptr;
		break;

	case UnitType::SHIELD:	break;
	case UnitType::CLOWN:
		/*if (team == Team::TEAM_1) {
			for (auto iter : teamMgr->team1_unit) {
				if (Length(currentPos, iter->transform->GetLocalPos()) < 300.0f) {
					iter->GetComponent<UnitMovement>()->attackCurrentDelay
						= iter->GetComponent<UnitMovement>()->attackDelay * 0.75f;
				}
				else {
					iter->GetComponent<UnitMovement>()->attackCurrentDelay
						= iter->GetComponent<UnitMovement>()->attackDelay;
				}
			}
		}
		else if (team == Team::TEAM_2) {
			for (auto iter : teamMgr->team2_unit) {
				iter->GetComponent<UnitMovement>()->attackCurrentDelay;
			}
		}*/
		break;
	case UnitType::GISAENG:
		attackTarget = nullptr;

		if (team == Team::TEAM_1) {
			for (auto iter : teamMgr->team1_unit) {
				float cel;
				auto tmp = iter->GetComponent<UnitMovement>();
				cel = tmp->hp / tmp->maxHp;

				if (cel < min) {
					attackTarget = tmp;
					min = cel;
				}
			}
		}
		else if (team == Team::TEAM_2) {
			for (auto iter : teamMgr->team2_unit) {
				float cel;
				auto tmp = iter->GetComponent<UnitMovement>();
				cel = tmp->hp / tmp->maxHp;

				if (cel < min) {
					attackTarget = tmp;
					min = cel;
				}
			}
		}

		if (attackTarget != nullptr) {
			attackTarget->GetDamage(attackPower);
			CLogger::Info("HEAL : %d", attackTarget->GetOwner()->GetEntityID());
		}
			
		break;
	default:				break;
	}
}

void UnitMovement::InitType(Team team, UnitType type)
{
	this->team = team;
	this->type = type;

	_anim = GetOwner()->GetComponent<AnimationController>();
	renderer = GetOwner()->GetComponent<Sprite2DRenderer>();
	tr = GetOwner()->GetComponent<Transform>();
	rectColl = GetOwner()->GetComponent<RectCollider>();

	teamMgr = GetOwner()->GetScene()->FindGameObject("TeamMgr")->GetComponent<TeamManager>();

	SpriteAnimation* anim_Idle = new SpriteAnimation();
	SpriteAnimation* anim_move = new SpriteAnimation();
	SpriteAnimation* anim_attack = new SpriteAnimation();

	//Animation등록
	switch (type)
	{
	case UnitType::NONE:
		break;

	case UnitType::SWORD:
		anim_Idle->SetFps(1);
		anim_Idle->AddTexture("Resources/Character/칼병/Idle/0.png");

		anim_move->SetFps(8);
		anim_move->AddTexture("Resources/Character/칼병/Walk/1.png");
		anim_move->AddTexture("Resources/Character/칼병/Walk/2.png");

		anim_attack->SetFps(2);
		anim_attack->AddTexture("Resources/Character/칼병/Attack/1.png");
		anim_attack->AddTexture("Resources/Character/칼병/Attack/2.png");

		renderer->SetTexture("Resources/Character/칼병/Idle/0.png");

		attackDelay = 1.3f;
		attackRange = 100.0f;
		attackPower = 20.0f;
		maxHp = 100;
		hp = maxHp;
		break;

	case UnitType::BOW:
		anim_Idle->SetFps(1);
		anim_Idle->AddTexture("Resources/Character/활병/Walk/1.png");

		anim_move->SetFps(8);
		anim_move->AddTexture("Resources/Character/활병/Walk/1.png");
		anim_move->AddTexture("Resources/Character/활병/Walk/2.png");

		anim_attack->SetFps(2);
		anim_attack->AddTexture("Resources/Character/활병/Attack/1.png");
		anim_attack->AddTexture("Resources/Character/활병/Attack/2.png");
		anim_attack->AddTexture("Resources/Character/활병/Attack/3.png");

		renderer->SetTexture("Resources/Character/활병/Walk/1.png");

		attackDelay = 1.3f;
		attackRange = 300.0f;
		attackPower = 5;
		maxHp = 60;
		hp = maxHp;
		break;
	case UnitType::SHIELD:
		anim_Idle->SetFps(1);
		anim_Idle->AddTexture("Resources/Character/방패병/Idle/1.png");

		anim_move->SetFps(8);
		anim_move->AddTexture("Resources/Character/방패병/Walk/1.png");
		anim_move->AddTexture("Resources/Character/방패병/Walk/2.png");

		anim_attack->SetFps(1);
		anim_attack->AddTexture("Resources/Character/방패병/Idle/1.png");

		renderer->SetTexture("Resources/Character/방패병/Idle/1.png");

		attackDelay = 1.3f;
		attackPower = 20.0f;
		attackRange = 100.0f;
		maxHp = 220;
		hp = maxHp;
		break;
	case UnitType::SLAVE:
		anim_Idle->SetFps(1);
		anim_Idle->AddTexture("Resources/Character/노비/Idle/1.png");

		anim_move->SetFps(8);
		anim_move->AddTexture("Resources/Character/노비/Walk/1.png");
		anim_move->AddTexture("Resources/Character/노비/Walk/2.png");
		anim_move->AddTexture("Resources/Character/노비/Walk/1.png");

		anim_attack->SetFps(2);
		anim_attack->AddTexture("Resources/Character/노비/Attack/1.png");
		anim_attack->AddTexture("Resources/Character/노비/Attack/2.png");

		renderer->SetTexture("Resources/Character/노비/Idle/1.png");

		attackDelay = 1.5f;
		attackPower = 20.0f;
		attackRange = 100.0f;
		maxHp = 350;
		hp = maxHp;
		break;
	case UnitType::MONKS:
		anim_Idle->SetFps(1);
		anim_Idle->AddTexture("Resources/Character/승려/Idle/1.png");

		anim_move->SetFps(8);
		anim_move->AddTexture("Resources/Character/승려/Walk/1.png");
		anim_move->AddTexture("Resources/Character/승려/Walk/2.png");
		anim_move->AddTexture("Resources/Character/승려/Walk/3.png");
		anim_move->AddTexture("Resources/Character/승려/Walk/4.png");

		anim_attack->SetFps(2);
		anim_attack->AddTexture("Resources/Character/승려/Attack/1.png");
		anim_attack->AddTexture("Resources/Character/승려/Attack/2.png");
		anim_attack->AddTexture("Resources/Character/승려/Attack/3.png");
		anim_attack->AddTexture("Resources/Character/승려/Attack/4.png");

		renderer->SetTexture("Resources/Character/승려/Idle/1.png");

		attackDelay = 1.5f;
		attackPower = 30;
		maxHp = 500;
		hp = maxHp;
		break;
	case UnitType::BUTCHRE:
		anim_Idle->SetFps(1);
		anim_Idle->AddTexture("Resources/Character/백정/Idle/1.png");

		anim_move->SetFps(8);
		anim_move->AddTexture("Resources/Character/백정/Walk/1.png");
		anim_move->AddTexture("Resources/Character/백정/Walk/2.png");

		anim_attack->SetFps(2);
		anim_attack->AddTexture("Resources/Character/백정/Attack/1.png");
		anim_attack->AddTexture("Resources/Character/백정/Attack/2.png");

		renderer->SetTexture("Resources/Character/기생/Idle/1.png");

		attackDelay = 1.5f;
		attackPower = 40;
		maxHp = 130;
		hp = maxHp;
		break;
	case UnitType::CLOWN:
		anim_Idle->SetFps(1);
		anim_Idle->AddTexture("Resources/Character/광대/Idle/1.png");

		anim_move->SetFps(9);
		anim_move->AddTexture("Resources/Character/광대/Walk/1.png");
		anim_move->AddTexture("Resources/Character/광대/Walk/2.png");
		anim_move->AddTexture("Resources/Character/광대/Walk/3.png");

		anim_attack->SetFps(20);
		anim_attack->AddTexture("Resources/Character/광대/Walk/1.png");
		anim_attack->AddTexture("Resources/Character/광대/Walk/2.png");
		anim_attack->AddTexture("Resources/Character/광대/Walk/3.png");

		renderer->SetTexture("Resources/Character/광대/Idle/1.png");

		attackDelay = 1.3f;
		attackPower = 20.0f;
		attackRange = 200.0f;
		maxHp = 50;
		hp = maxHp;
		break;
	case UnitType::GISAENG:
		anim_Idle->SetFps(1);
		anim_Idle->AddTexture("Resources/Character/기생/Idle/1.png");

		anim_move->SetFps(8);
		anim_move->AddTexture("Resources/Character/기생/Walk/1.png");
		anim_move->AddTexture("Resources/Character/기생/Walk/2.png");

		anim_attack->SetFps(2);
		anim_attack->AddTexture("Resources/Character/기생/Attack/1.png");
		anim_attack->AddTexture("Resources/Character/기생/Attack/2.png");

		renderer->SetTexture("Resources/Character/기생/Idle/1.png");

		attackDelay = 0.1f;
		attackPower = -0.5f;
		maxHp = 50;
		hp = maxHp;
		attackRange = 500.0f;
		break;
	default:
		break;
	}
	GameObject* barObj = new GameObject();
	GetOwner()->transform->AddChild(barObj->transform);
	bar = barObj->AddComponent<UIHp>();

	if (team == Team::TEAM_1) {
		bar->SetTexture("Resources/UI/team1_hp.png");
	}
	if (team == Team::TEAM_2) {
		tr->SetScale(-tr->GetScale().x, tr->GetScale().y);
		bar->SetTexture("Resources/UI/team2_hp.png");
	}
	barObj->transform->SetLocalPos(Vec2(renderer->GetWidth() / 2.0f, -20) - bar->GetTextureSize() / 2.0f);

	attackCurrentDelay = attackDelay;
	
	_anim->AddAnimationNode("Idle", anim_Idle);
	_anim->AddAnimationNode("Move", anim_move);
	_anim->AddAnimationNode("Attack", anim_attack);
	_anim->SetEntryAnimationNode("Idle");

	_anim->AddParameter<bool>("IsWalk", false);
	_anim->AddParameter<bool>("IsAttack", false);

	moveSpeed = 66.0f;

	//Move
	_anim->SetHasExitTime("Idle", "Move", false);
	_anim->SetHasExitTime("Move", "Idle", false);
	_anim->AddState<bool>("Idle", "IsWalk", EQUALS, true, "Move");
	_anim->AddState<bool>("Move", "IsWalk", EQUALS, false, "Idle");
	
	//Attack
	_anim->SetHasExitTime("Idle", "Attack", false);
	_anim->SetHasExitTime("Attack", "Idle", false);
	_anim->AddState<bool>("Idle", "IsAttack", EQUALS, true, "Attack");
	_anim->AddState<bool>("Attack", "IsAttack", EQUALS, false, "Idle");

	if (type == UnitType::CLOWN) {
		if (team == Team::TEAM_1) {
			for (auto iter : teamMgr->team1_unit) {
				iter->GetComponent<UnitMovement>()->attackCurrentDelay =
					Clamp(iter->GetComponent<UnitMovement>()->attackCurrentDelay - 0.2f,
						iter->GetComponent<UnitMovement>()->attackDelay,
						iter->GetComponent<UnitMovement>()->attackDelay < 0.3f ? iter->GetComponent<UnitMovement>()->attackDelay : 0.3f);
			}
		}
		if (team == Team::TEAM_2) {
			for (auto iter : teamMgr->team2_unit) {
				iter->GetComponent<UnitMovement>()->attackCurrentDelay =
					Clamp(iter->GetComponent<UnitMovement>()->attackCurrentDelay - 0.2f,
						iter->GetComponent<UnitMovement>()->attackDelay,
						iter->GetComponent<UnitMovement>()->attackDelay < 0.3f ? iter->GetComponent<UnitMovement>()->attackDelay : 0.3f);
			}
		}
	}

	rectColl->SetRect(renderer->GetVisibleRect());
}

void UnitMovement::GetDamage(float damage)
{
	if (hp - damage < maxHp) {
		hp -= damage;
	}
	else {
		hp = maxHp;
	}

	if (hp <= 0.0f) {
		if (type == UnitType::CLOWN) {
			if (team == Team::TEAM_1) {
				for (auto iter : teamMgr->team1_unit) {
					iter->GetComponent<UnitMovement>()->attackCurrentDelay += 0.2f;
				}
			}
			if (team == Team::TEAM_2) {
				for (auto iter : teamMgr->team2_unit) {
					iter->GetComponent<UnitMovement>()->attackCurrentDelay += 0.2f;
				}
			}
		}
	}
}