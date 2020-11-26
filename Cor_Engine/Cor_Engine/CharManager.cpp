#include "stdafx.h"
#include "CharManager.h"
#include "ZeroSystem.h"
#include "GameObject.h"
#include "Sprite2DRenderer.h"
#include "CharMovement.h"
#include "Transform.h"

void CharManager::Update()
{
	if (true) {
		GameObject* c = new GameObject();
		c->AddComponent<Sprite2DRenderer>()->SetTexture("Resources/Character/Sword/Idle/1.png");
		c->AddComponent<CharMovement>();
		c->GetComponent<Transform>()->SetLocalPos(Vec2(1280/2 - 100,720/2));
		std::cout << "Create Entity : " << c->GetEntityID() << std::endl;
	}
}
