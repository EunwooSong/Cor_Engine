#include "stdafx.h"
#include "GameScene.h"
#include "GameObject.h"
#include "CharManager.h"
#include "CharMovement.h"
#include "Transform.h"
#include "Sprite2DRenderer.h"

GameScene::GameScene() {
}

GameScene::~GameScene() {
}

void GameScene::Init() {
	Scene::Init();

	RegisterComponent<CharManager>();
	RegisterComponent<CharMovement>();

	GameObject* bg = new GameObject();
	bg->AddComponent<Sprite2DRenderer>()->SetTexture("Resources/Stage/Map.png");
	bg->transform->SetScale(Vec2(10.0f, 10.0f));

	GameObject* charManager = new GameObject();
	charManager->AddComponent<CharManager>();
}