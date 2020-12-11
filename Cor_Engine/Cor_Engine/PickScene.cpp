#include "stdafx.h"
#include "PickScene.h"
#include "GameObject.h"
#include "PickSceneManager.h"
#include "Sprite2DRenderer.h"
#include "Transform.h"

void PickScene::Init()
{
	Scene::Init();

	RegisterComponent<PickSceneManager>();

	Vec2 originPos = Vec2(1280, 720) / 2.0f;
	Vec2 offset = Vec2(150,0);

	GameObject* bg = new GameObject();
	bg->AddComponent<Sprite2DRenderer>()->SetTexture("Resources/Stage/stage_pick.png");

	GameObject* type_1 = new GameObject();
	type_1->AddComponent<Sprite2DRenderer>()->SetTexture("Resources/UI/Character Icon/³ëºñui.png");
	type_1->transform->SetLocalPos(originPos + offset * -2 - Vec2(50, 50));

	GameObject* type_2 = new GameObject();
	type_2->AddComponent<Sprite2DRenderer>()->SetTexture("Resources/UI/Character Icon/½Â·Áui.png");
	type_2->transform->SetLocalPos(originPos + offset * -1 - Vec2(50, 50));

	GameObject* type_3 = new GameObject();
	type_3->AddComponent<Sprite2DRenderer>()->SetTexture("Resources/UI/Character Icon/¹éÁ¤ui.png");
	type_3->transform->SetLocalPos(originPos + offset * 0 - Vec2(50, 50));

	GameObject* type_4 = new GameObject();
	type_4->AddComponent<Sprite2DRenderer>()->SetTexture("Resources/UI/Character Icon/±¤´ëui.png");
	type_4->transform->SetLocalPos(originPos + offset * 1 - Vec2(50, 50));

	GameObject* type_5 = new GameObject();
	type_5->AddComponent<Sprite2DRenderer>()->SetTexture("Resources/UI/Character Icon/±â»ýui.png");
	type_5->transform->SetLocalPos(originPos + offset * 2 - Vec2(50, 50));

	GameObject* obj = new GameObject();
	obj->AddComponent<PickSceneManager>();
	obj->GetComponent<PickSceneManager>()->typeList[0] = type_1;
	obj->GetComponent<PickSceneManager>()->typeList[1] = type_2;
	obj->GetComponent<PickSceneManager>()->typeList[2] = type_3;
	obj->GetComponent<PickSceneManager>()->typeList[3] = type_4;
	obj->GetComponent<PickSceneManager>()->typeList[4] = type_5;
}
