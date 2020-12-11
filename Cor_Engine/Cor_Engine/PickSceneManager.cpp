#include "stdafx.h"
#include "GameObject.h"
#include "PickSceneManager.h"
#include "Sprite2DRenderer.h"
#include "ZeroSystem.h"
#include "Transform.h"
#include "GameScene.h"
#include "Button.h"

void PickSceneManager::Start()
{
	Component::Start();

	pick_1_ui = new GameObject();
	pick_1_ui->AddComponent<Sprite2DRenderer>();
	pick_1_ui->GetComponent<Sprite2DRenderer>()->SetTexture("Resources/UI/user_choiced.png");
	pick_1_ui->GetComponent<Sprite2DRenderer>()->SetColor(D3DXCOLOR( 1.0f, 0.8f, 0.4f, 1.0f));
	pick_1_ui->transform->SetScaleCenter(Vec2(50,50));

	pick_2_ui = new GameObject();
	pick_2_ui->AddComponent<Sprite2DRenderer>();
	pick_2_ui->GetComponent<Sprite2DRenderer>()->SetTexture("Resources/UI/user_choiced.png");
	pick_2_ui->GetComponent<Sprite2DRenderer>()->SetColor(D3DXCOLOR(0.415f, 0.929f, 0.455f, 1.0f));
	pick_2_ui->transform->SetScaleCenter(Vec2(50, 50));

	btn_start = new GameObject();
	btn_start->AddComponent<Sprite2DRenderer>();
	btn_start->AddComponent<Button>()->SetTextureImage("Resources/UI/btn_gamestart.png");
	btn_start->SetIsActive(false);
	btn_start->GetComponent<Button>()->SetDefScale(Vec2(0.7f, 0.7f));
	btn_start->GetComponent<Button>()->SetUpScale(Vec2(0.85f, 0.85f));
	btn_start->GetComponent<Button>()->SetOnClick([&]() {
		auto iter = new GameScene();
		iter->arr[0][0] = typeList_1[0];
		iter->arr[0][1] = typeList_1[1];
		iter->arr[0][2] = typeList_1[2];

		iter->arr[1][0] = typeList_2[0];
		iter->arr[1][1] = typeList_2[1];
		iter->arr[1][2] = typeList_2[2];
		ZERO_SCENE_MGR->ChangeScene(iter);
		});
	btn_start->transform->SetLocalPos(Vec2(1280 / 2.0f, 650.0f) - btn_start->GetComponent<Sprite2DRenderer>()->GetTextureSize() / 2);
}

void PickSceneManager::Update()
{
	Component::Update();

	timer += ZERO_TIME_MGR->GetDeltaTime();

	pick_1_ui->transform->SetScale(Vec2(1.0f, 1.0f) + Vec2(0.1f, 0.1f) * sin(timer * 3));
	pick_2_ui->transform->SetScale(Vec2(1.0f, 1.0f) + Vec2(0.1f, 0.1f) * sin(timer * 3) * -1);

	pick_1_ui->transform->SetLocalPos(typeList[index_1]->transform->GetLocalPos());
	pick_2_ui->transform->SetLocalPos(typeList[index_2]->transform->GetLocalPos());

	if (ZERO_INPUT_MGR->GetKeyState('A') == KEY_DOWN) {
		if(index_1 > 0)
		index_1--;
	}
	else if (ZERO_INPUT_MGR->GetKeyState('D') == KEY_DOWN) {
		if(index_1 < 4)
			index_1++;
	}
	
	Clamp(index_1, 0, 4);

	if (ZERO_INPUT_MGR->GetKeyState(' ') == KEY_DOWN) {
		if (count_1 < 3)
		{
			bool c = false;
			for (UnitType type : typeList_1) {
				if ((int)type == index_1 + 3) {
					c = true;
				}
			}

			if (!c) {
				AddType(Team::TEAM_1, (UnitType)(index_1 + 3));
			}
		}		
	}

	if (ZERO_INPUT_MGR->GetKeyState(VK_LEFT) == KEY_DOWN) {
		if(index_2 > 0)
			index_2--;
	}
	else if (ZERO_INPUT_MGR->GetKeyState(VK_RIGHT) == KEY_DOWN) {
		if(index_2 < 4)
			index_2++;
	}

	if (ZERO_INPUT_MGR->GetKeyState(VK_RETURN) == KEY_DOWN) {
		if (count_2 < 3)
		{
			bool c = false;
			for (UnitType type : typeList_2) {
				if ((int)type == index_2 + 3) {
					c = true;
				}
			}

			if (!c) {
				AddType(Team::TEAM_2, (UnitType)(index_2 + 3));
			}
		}
	}

	if (count_1 == 3 && count_2 == 3) {
		if(!btn_start->GetIsActive())
			btn_start->SetIsActive(true);
	}
}

void PickSceneManager::AddType(Team team, UnitType type)
{
	Vec2 origin_1 = Vec2(20, 600);
	Vec2 origin_2 = Vec2(1280 - 20, 600);
	
	Vec2 offset = Vec2(100, 0);

	GameObject* obj = new GameObject();
	Sprite2DRenderer* sprite = obj->AddComponent<Sprite2DRenderer>();
	obj->transform->SetScale(Vec2(0.8f, 0.8f));
	switch (type)
	{
	case UnitType::SLAVE:
		sprite->SetTexture("Resources/UI/Character Icon/³ëºñui.png");
		break;
	case UnitType::MONKS:
		sprite->SetTexture("Resources/UI/Character Icon/½Â·Áui.png");
		break;
	case UnitType::BUTCHRE:
		sprite->SetTexture("Resources/UI/Character Icon/¹éÁ¤ui.png");
		break;
	case UnitType::CLOWN:
		sprite->SetTexture("Resources/UI/Character Icon/±¤´ëui.png");
		break;
	case UnitType::GISAENG:
		sprite->SetTexture("Resources/UI/Character Icon/±â»ýui.png");
		break;
	default:
		break;
	}

	if (team == Team::TEAM_1) {
		typeList_1[count_1] = type;
		count_1++;
		obj->transform->SetLocalPos(origin_1 + offset * count_1);
	}
	else if (team == Team::TEAM_2) {
		typeList_2[count_2] = type;
		count_2++;
		obj->transform->SetLocalPos(origin_2 + offset * count_2 * - 1);
	}
}
