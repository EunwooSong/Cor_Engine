#include "stdafx.h"
#include "BulletMovement.h"
#include "GameObject.h"
#include "Sprite2DRenderer.h"
#include "Transform.h"
#include "ZeroSystem.h"
#include "RectCollider.h"

BulletMovement::BulletMovement() : moveSpeed(200.0f), timer(0.0f)
{
}

BulletMovement::~BulletMovement()
{
}

void BulletMovement::Start()
{
	Component::Start();

	tr = GetOwner()->transform;
}

void BulletMovement::Update() {
	Component::Update();

	timer += ZERO_TIME_MGR->GetDeltaTime();
	Vec2 moveDir = Vec2(0,0);

	if (team == Team::TEAM_1)
		moveDir.x = 1.0f;
	else if (team == Team::TEAM_2)
		moveDir.x = -1.0f;

	tr->Translate(moveDir * ZERO_TIME_MGR->GetDeltaTime() * moveSpeed);

	if (timer > 1.5f)
		GameObject::Destroy(GetOwner());
}

void BulletMovement::InitBullet(Team team, BulletType type, float damage)
{
	this->type = type;
	this->team = team;
	this->damage = damage;

	if (type == BulletType::ARROW) {
		Sprite2DRenderer* tmp = GetOwner()->AddComponent<Sprite2DRenderer>();
		tmp->SetTexture("Resources/Bullet/arrow.png");

		if (team == Team::TEAM_2) {
			GetOwner()->transform->SetScale(Vec2(-1.0f, 1.0f));
			GetOwner()->GetComponent<RectCollider>()->SetRect(Rect(Vec2(tmp->GetTextureSize().x * -1, 0), Vec2(0, tmp->GetTextureSize().y)));
		}
		else	
			GetOwner()->GetComponent<RectCollider>()->SetRect(Rect(tmp->GetTextureSize()));
	}
}