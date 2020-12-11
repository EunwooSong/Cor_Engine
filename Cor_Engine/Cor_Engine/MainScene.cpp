#include "stdafx.h"
#include "MainScene.h"
#include "GameObject.h"
#include "Sprite2DRenderer.h"
#include "Button.h"
#include "ZeroSystem.h"
#include "Transform.h"
#include "GameScene.h"

#include "PickScene.h"

MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}

void MainScene::Init()
{
	Scene::Init();

	GameObject* bg = new GameObject();
	bg->AddComponent<Sprite2DRenderer>()->SetTexture("Resources/Stage/stage_1.png");

	GameObject* obj = new GameObject();
	obj->AddComponent<Sprite2DRenderer>()->SetTexture("Resources/UI/Logo.png");
	obj->transform->SetLocalPos(Vec2(1280 / 2.0f - obj->GetComponent<Sprite2DRenderer>()->GetWidth() / 2.0f, 25.0f));

	GameObject* btn = new GameObject();
	btn->AddComponent<Sprite2DRenderer>();
	btn->AddComponent<Button>()->SetTextureImage("Resources/UI/btn_start.png");
	btn->GetComponent<Button>()->SetOnClick([&]() {
		ZERO_SCENE_MGR->ChangeScene(new PickScene());
		});
	btn->transform->SetLocalPos(Vec2(1280/2.0f, 650.0f) - btn->GetComponent<Sprite2DRenderer>()->GetTextureSize()/2.0f);
	btn->GetComponent<Button>()->SetDefScale(Vec2(0.6f, 0.6f));
	btn->GetComponent<Button>()->SetUpScale(Vec2(0.7f, 0.7f));

	btn = new GameObject();
	btn->AddComponent<Sprite2DRenderer>();
	btn->AddComponent<Button>()->SetTextureImage("Resources/UI/btn_help.png");
	btn->GetComponent<Button>()->SetOnClick([&]() {
		GameObject* obj = new GameObject();
		obj->AddComponent<Sprite2DRenderer>();
		obj->AddComponent<Button>()->SetTextureImage("Resources/UI/helpbackground.png");
		obj->transform->SetLocalPos(Vec2(0.0f, 0.0f));
		obj->transform->SetScale(Vec2(0.0f, 0.0f));
		obj->GetComponent<Button>()->SetDefScale(Vec2(1.0f, 1.0f));
		obj->GetComponent<Button>()->SetUpScale(Vec2(1.0f, 1.0f));
		});
	btn->transform->SetLocalPos(Vec2(1280 / 2.0f, 650.0f) - btn->GetComponent<Sprite2DRenderer>()->GetTextureSize() / 2.0f + Vec2(300.0f,0.0f));
	btn->GetComponent<Button>()->SetDefScale(Vec2(0.6f, 0.6f));
	btn->GetComponent<Button>()->SetUpScale(Vec2(0.7f, 0.7f));
}
