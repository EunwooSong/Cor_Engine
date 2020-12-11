#include "stdafx.h"
#include "ResultScene.h"
#include "GameObject.h"
#include "MainScene.h"
#include "Sprite2DRenderer.h"
#include "ZeroSystem.h"
#include "Button.h"
#include "Transform.h"

void ResultScene::Init()
{
	Scene::Init();

	GameObject* bg = new GameObject();
	Sprite2DRenderer* renderer = bg->AddComponent<Sprite2DRenderer>();
	if (winTeam == Team::TEAM_1) {
		renderer->SetTexture("Resources/Stage/result_left.png");
	}
	else if (winTeam == Team::TEAM_2) {
		renderer->SetTexture("Resources/Stage/result_right.png");
	}

	GameObject* btn = new GameObject();
	btn->AddComponent<Sprite2DRenderer>();
	btn->AddComponent<Button>()->SetTextureImage("Resources/UI/btn_home.png");
	btn->GetComponent<Button>()->SetOnClick([&]() {
		ZERO_SCENE_MGR->ChangeScene(new MainScene());
		});
	btn->transform->SetLocalPos(Vec2(1280 / 2.0f, 650.0f) - btn->GetComponent<Sprite2DRenderer>()->GetTextureSize() / 2.0f);
	btn->GetComponent<Button>()->SetDefScale(Vec2(0.6f, 0.6f));
	btn->GetComponent<Button>()->SetUpScale(Vec2(0.7f, 0.7f));
} 