#include "stdafx.h"
#include "TestScene.h"
#include "GameObject.h"
#include "Transform.h"
#include "Sprite2DRenderer.h"
#include "BoxCollider.h"
#include "RigidBody2D.h"

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}

void TestScene::Init()
{
	Scene::Init();

	GameObject* tmp = new GameObject();
	tmp->AddComponent<Sprite2DRenderer>()->SetTexture("Resources/Character/Sword/Idle/1.PNG");
	tmp->AddComponent<BoxCollider>();
	tmp->AddComponent<RigidBody2D>();
	tmp->GetComponent<Transform>();

	//tmp = new GameObject();
	//tmp->AddComponent<Sprite2DRenderer>()->SetTexture("");
	//tmp->AddComponent<BoxCollider>();
	//tmp->AddComponent<RigidBody2D>();
	//tmp->GetComponent<Transform>();
}
