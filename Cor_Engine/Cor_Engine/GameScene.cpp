#include "stdafx.h"
#include "GameScene.h"
#include "GameObject.h"
#include "TeamManager.h"
#include "UnitMovement.h"
#include "Transform.h"
#include "Sprite2DRenderer.h"

GameScene::GameScene() {
}

GameScene::~GameScene() {
}

void GameScene::Init() {
	Scene::Init();

	RegisterComponent<TeamManager>();
	RegisterComponent<UnitMovement>();

	GameObject* bg = new GameObject();
	bg->AddComponent<Sprite2DRenderer>()->SetTexture("Resources/Stage/Map.png");
	bg->transform->SetScale(Vec2(10.0f, 10.0f));

	//팀 메니저 등록
	GameObject* teamManager = new GameObject();
	teamManager->SetName("TeamMgr");
	teamManager->AddComponent<TeamManager>();
}