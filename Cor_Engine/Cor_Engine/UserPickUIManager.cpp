#include "stdafx.h"
#include "UserPickUIManager.h"
#include "Sprite2DRenderer.h"
#include "Transform.h"
#include "UIImageRenderer.h"
#include "ZeroSystem.h"
#include "UIText.h"

UserPickUIManager::UserPickUIManager() : timer(0.0f), team1_pick(0), team2_pick(0)
{
}

UserPickUIManager::~UserPickUIManager()
{
}

void UserPickUIManager::Start()
{
	Component::Start();

	teamMGR = GetOwner()->GetScene()->FindGameObject("TeamMgr")->GetComponent<TeamManager>();
}

void UserPickUIManager::Update()
{
	Component::Update();

	timer += ZERO_TIME_MGR->GetDeltaTime();

	pick_ui_1->transform->SetScale(Vec2(1.0f, 1.0f) + Vec2(0.1f, 0.1f) * sin(timer * 3.0f));
	pick_ui_2->transform->SetScale(Vec2(1.0f, 1.0f) + Vec2(0.1f, 0.1f) * sin(timer * 3.0f));

	pick_ui_1->transform->SetLocalPos(team1_ui[teamMGR->team1_currentIndex]->transform->GetLocalPos());
	pick_ui_2->transform->SetLocalPos(team2_ui[teamMGR->team2_currentIndex]->transform->GetLocalPos());

	money_text_1->SetText(std::to_string(teamMGR->money_1))->SetRect(-1);
	money_text_2->SetText(std::to_string(teamMGR->money_2))->SetRect(-1);
}

void UserPickUIManager::Init(UnitType* arr1, UnitType* arr2)
{
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			//TEAM 1 -----------
			UnitType type = arr1[i * 3 + j];
			Vec2 pos = Vec2(20, 20) + Vec2(j * 125, 125 * i);

			GameObject* tmp = new GameObject();
			tmp->AddComponent<UIImageRenderer>();
			team1_ui[i * 3 + j] = tmp;

			switch (type)
			{
			case UnitType::NONE:
				break;
			case UnitType::SWORD:
				tmp->GetComponent<UIImageRenderer>()->SetTexture("Resources/UI/Character Icon/Ä®º´ui.png");
				tmp->AddComponent<UIText>()->SetText(std::to_string(teamMGR->cost[0]))->SetFont("¸¼Àº°íµñ");
				break;
			case UnitType::BOW:
				tmp->GetComponent<UIImageRenderer>()->SetTexture("Resources/UI/Character Icon/È°º´ui.png");
				tmp->AddComponent<UIText>()->SetText(std::to_string(teamMGR->cost[1]))->SetFont("¸¼Àº°íµñ");
				break;
			case UnitType::SHIELD:
				tmp->GetComponent<UIImageRenderer>()->SetTexture("Resources/UI/Character Icon/¹æÆÐº´ui.png");
				tmp->AddComponent<UIText>()->SetText(std::to_string(teamMGR->cost[2]))->SetFont("¸¼Àº°íµñ");
				break;
			case UnitType::SLAVE:
				tmp->GetComponent<UIImageRenderer>()->SetTexture("Resources/UI/Character Icon/³ëºñui.png");
				tmp->AddComponent<UIText>()->SetText(std::to_string(teamMGR->cost[3]))->SetFont("¸¼Àº°íµñ");
				break;
			case UnitType::MONKS:
				tmp->GetComponent<UIImageRenderer>()->SetTexture("Resources/UI/Character Icon/½Â·Áui.png");
				tmp->AddComponent<UIText>()->SetText(std::to_string(teamMGR->cost[4]))->SetFont("¸¼Àº°íµñ");
				break;
			case UnitType::BUTCHRE:
				tmp->GetComponent<UIImageRenderer>()->SetTexture("Resources/UI/Character Icon/¹éÁ¤ui.png");
				tmp->AddComponent<UIText>()->SetText(std::to_string(teamMGR->cost[5]))->SetFont("¸¼Àº°íµñ");
				break;
			case UnitType::CLOWN:
				tmp->GetComponent<UIImageRenderer>()->SetTexture("Resources/UI/Character Icon/±¤´ëui.png");
				tmp->AddComponent<UIText>()->SetText(std::to_string(teamMGR->cost[6]))->SetFont("¸¼Àº°íµñ");
				break;
			case UnitType::GISAENG:
				tmp->GetComponent<UIImageRenderer>()->SetTexture("Resources/UI/Character Icon/±â»ýui.png");
				tmp->AddComponent<UIText>()->SetText(std::to_string(teamMGR->cost[7]))->SetFont("¸¼Àº°íµñ");
				break;
			default:
				break;
			}
			tmp->transform->SetLocalPos(pos);

			//TEAM 2 -----------
			type = arr2[i * 3 + j];
			pos = Vec2(1280 - 20, 20) + Vec2((j + 1) * -125, 125 * i);

			tmp = new GameObject();
			tmp->AddComponent<UIImageRenderer>();
			team2_ui[i * 3 + j] = tmp;
			switch (type)
			{
			case UnitType::NONE:
				break;
			case UnitType::SWORD:
				tmp->GetComponent<UIImageRenderer>()->SetTexture("Resources/UI/Character Icon/Ä®º´ui.png");
				tmp->AddComponent<UIText>()->SetText(std::to_string(teamMGR->cost[0]))->SetFont("¸¼Àº°íµñ");
				break;
			case UnitType::BOW:
				tmp->GetComponent<UIImageRenderer>()->SetTexture("Resources/UI/Character Icon/È°º´ui.png");
				tmp->AddComponent<UIText>()->SetText(std::to_string(teamMGR->cost[1]))->SetFont("¸¼Àº°íµñ");
				break;
			case UnitType::SHIELD:
				tmp->GetComponent<UIImageRenderer>()->SetTexture("Resources/UI/Character Icon/¹æÆÐº´ui.png");
				tmp->AddComponent<UIText>()->SetText(std::to_string(teamMGR->cost[2]))->SetFont("¸¼Àº°íµñ");
				break;
			case UnitType::SLAVE:
				tmp->GetComponent<UIImageRenderer>()->SetTexture("Resources/UI/Character Icon/³ëºñui.png");
				tmp->AddComponent<UIText>()->SetText(std::to_string(teamMGR->cost[3]))->SetFont("¸¼Àº°íµñ");
				break;
			case UnitType::MONKS:
				tmp->GetComponent<UIImageRenderer>()->SetTexture("Resources/UI/Character Icon/½Â·Áui.png");
				tmp->AddComponent<UIText>()->SetText(std::to_string(teamMGR->cost[4]))->SetFont("¸¼Àº°íµñ");
				break;
			case UnitType::BUTCHRE:
				tmp->GetComponent<UIImageRenderer>()->SetTexture("Resources/UI/Character Icon/¹éÁ¤ui.png");
				tmp->AddComponent<UIText>()->SetText(std::to_string(teamMGR->cost[5]))->SetFont("¸¼Àº°íµñ");
				break;
			case UnitType::CLOWN:
				tmp->GetComponent<UIImageRenderer>()->SetTexture("Resources/UI/Character Icon/±¤´ëui.png");
				tmp->AddComponent<UIText>()->SetText(std::to_string(teamMGR->cost[6]))->SetFont("¸¼Àº°íµñ");
				break;
			case UnitType::GISAENG:
				tmp->GetComponent<UIImageRenderer>()->SetTexture("Resources/UI/Character Icon/±â»ýui.png");
				tmp->AddComponent<UIText>()->SetText(std::to_string(teamMGR->cost[7]))->SetFont("¸¼Àº°íµñ");
				break;
			default:
				break;
			}
			tmp->transform->SetLocalPos(pos);
		}
	}

	pick_ui_1 = new GameObject();
	pick_ui_1->AddComponent<UIImageRenderer>()->SetTexture("Resources/UI/choiced.png");
	pick_ui_1->transform->SetScaleCenter(pick_ui_1->GetComponent<UIImageRenderer>()->GetTextureSize() / 2.0f);
	pick_ui_1->transform->SetLocalPos(team1_ui[0]->transform->GetLocalPos());

	pick_ui_2 = new GameObject();
	pick_ui_2->AddComponent<UIImageRenderer>()->SetTexture("Resources/UI/choiced.png");
	pick_ui_2->transform->SetScaleCenter(pick_ui_1->GetComponent<UIImageRenderer>()->GetTextureSize() / 2.0f);
	pick_ui_2->transform->SetLocalPos(team2_ui[0]->transform->GetLocalPos());

	GameObject* money = new GameObject();
	money->AddComponent<UIImageRenderer>()->SetTexture("Resources/UI/coin.png");
	money->transform->SetLocalPos(Vec2(100, 300));
	money->transform->SetScale(Vec2(2.0f, 2.0f));

	money = new GameObject();
	money->AddComponent<UIImageRenderer>()->SetTexture("Resources/UI/coin.png");
	money->transform->SetLocalPos(Vec2(1280 - 300, 300));
	money->transform->SetScale(Vec2(-2.0f, 2.0f));

	GameObject* tmp = new GameObject();
	tmp->transform->SetLocalPos(Vec2(150, 300));
	money_text_1 = tmp->AddComponent<UIText>();
	money_text_1->SetSize(50)->SetText("0")->SetFont("¸¼Àº°íµñ");

	tmp = new GameObject();
	tmp->transform->SetLocalPos(Vec2(1280 - 250, 300));
	money_text_2 = tmp->AddComponent<UIText>();
	money_text_2->SetSize(50)->SetText("0")->SetFont("¸¼Àº°íµñ");
}
