#include "stdafx.h"
#include "RigidBodyTestScene.h"
#include "GameObject.h"
#include "Sprite2DRenderer.h"
#include "RigidBody2D.h"
#include "BoxCollider.h"
#include "Transform.h"

RigidBodyTestScene::RigidBodyTestScene()
{

}


RigidBodyTestScene::~RigidBodyTestScene()
{
}

void RigidBodyTestScene::Init() {
	Scene::Init();

	GameObject* rect1 = new GameObject();
	auto rect2 = new GameObject();

	rect1->AddComponent<Sprite2DRenderer>()->SetTexture("Resources/Stage/Map.png");
	rect2->AddComponent<Sprite2DRenderer>()->SetTexture("Resources/Stage/Map.png");
	rect1->transform->SetLocalPos(1280 / 2, 720 / 2);
	rect2->transform->SetLocalPos(1280 / 2, 720 / 2 + 200);
	rect1->transform->SetScale(1.0f, 1.0f);
	rect2->transform->SetScale(1.0f, 1.0f);

	//GameObject* bg = new GameObject();
	//bg->AddComponent<Sprite2DRenderer>()->SetTexture("Resources/Stage/Map.png");
	//bg->transform->SetScale(10.0f, 10.0f);



	auto rect1Collider = rect1->AddComponent<BoxCollider>();
	auto rect2Collider = rect2->AddComponent<BoxCollider>();
	rect1Collider->SetIsTrigger(true);
	rect2Collider->SetIsTrigger(true);
	rect1Collider->SetAbsolutePos(Vec2(1, 1), Vec2(1, 1), 1);
	rect2Collider->SetAbsolutePos(Vec2(100, 100), Vec2(1, 1), 0);
	rect1->AddComponent<RigidBody2D>()->SetGravity(9.8);
	rect2->AddComponent<RigidBody2D>()->SetGravity(0.0);
}
