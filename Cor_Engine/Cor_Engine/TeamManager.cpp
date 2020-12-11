#include "stdafx.h"
#include "TeamManager.h"
#include "GameObject.h"
#include "ZeroSystem.h"
#include "UnitBaseObject.h"
#include "UnitMovement.h"
#include "BulletMovement.h"
#include "ResultScene.h"
#include "Bullet.h"

TeamManager::TeamManager() : createUnit_1(false), createUnit_2(false), team1_currentIndex(0), team2_currentIndex(0),
defaultHp(600.0f), baseHp_1(600.0f), baseHp_2(600.0f), money_1(0), money_2(0), moneyTimer(0.0f), moneyDelay(1.0f), level_1(0), level_2(0),
createDelay_1(0.0f), createDelay_2(0.0f)
{
	indexArr1[3] = UnitType::SLAVE;
	indexArr1[4] = UnitType::MONKS;
	indexArr1[5] = UnitType::BUTCHRE;

	indexArr2[3] = UnitType::BUTCHRE;
	indexArr2[4] = UnitType::CLOWN;
	indexArr2[5] = UnitType::GISAENG;
}

TeamManager::~TeamManager()
{
}

void TeamManager::Start()
{
	Component::Start();
	teamHp_1 = new GameObject();
	teamHp_1->AddComponent<UIHp>()->SetTexture("Resources/UI/team1_hp.png");
	teamHp_1->transform->SetScale(Vec2(2.0f, 2.0f));
	teamBase1->transform->AddChild(teamHp_1->transform);
	teamHp_1->transform->SetLocalPos(Vec2(70.0f, -25.0f) - teamHp_1->GetComponent<UIHp>()->GetTextureSize());

	teamHp_2 = new GameObject();
	teamHp_2->AddComponent<UIHp>()->SetTexture("Resources/UI/team2_hp.png");
	teamHp_2->transform->SetScale(Vec2(2.0f, 2.0f));
	teamBase2->transform->AddChild(teamHp_2->transform);
	teamHp_2->transform->SetLocalPos(Vec2(70.0f, -25.0f) - teamHp_2->GetComponent<UIHp>()->GetTextureSize());
}

void TeamManager::Update()
{
	Component::Update();
	createDelay_1 += ZERO_TIME_MGR->GetDeltaTime();
	createDelay_2 += ZERO_TIME_MGR->GetDeltaTime();

	moneyTimer += ZERO_TIME_MGR->GetDeltaTime();

	if (ZERO_INPUT_MGR->GetKeyState('V') == KEY_DOWN) {
		money_1 += 1000;
		money_2 += 1000;
	}

	int money = 10;
	if (moneyTimer >= moneyDelay) {
		moneyTimer = 0.0f;
		money_1 += money + 10 * level_1;
		money_2 += money + 10 * level_2;
	}

	if (ZERO_INPUT_MGR->GetKeyState('Q') == KEY_DOWN) {
		if (money_1 >= 300) {
			if (level_1 < 1) {
				money_1 -= 300;
				level_1++;
				baseHp_1 = defaultHp * 2;
				teamBase1->GetComponent<Sprite2DRenderer>()->SetTexture("Resources/UI/기지/기지2.png");
			}
		}
	}
	if (ZERO_INPUT_MGR->GetKeyState('Y') == KEY_DOWN) {
		if (money_2 >= 300) {
			if (level_2 < 1) {
				money_2 -= 300;
				level_2++;
				baseHp_2 = defaultHp * 2;
				teamBase2->GetComponent<Sprite2DRenderer>()->SetTexture("Resources/UI/기지/기지2.png");
			}
		}
	}

	//Team1 생성 
	/*if (ZERO_INPUT_MGR->GetKeyState('1') == KEY_DOWN) {
		UnitBaseObject* obj = new UnitBaseObject();
		obj->GetComponent<UnitMovement>()->InitType(Team::TEAM_1, UnitType::SWORD);
		team1_unit.push_back(obj);
		obj->GetComponent<UnitMovement>()->myIter = team1_unit.begin() + (team1_unit.size() - 1);
		obj->transform->SetLocalPos(teamBase1->transform->GetLocalPos());
	}

	if (ZERO_INPUT_MGR->GetKeyState(VK_NUMPAD1) == KEY_DOWN) {
		UnitBaseObject* obj = new UnitBaseObject();
		obj->GetComponent<UnitMovement>()->InitType(Team::TEAM_2, UnitType::SWORD);
		team2_unit.push_back(obj);
		obj->GetComponent<UnitMovement>()->myIter = team2_unit.begin() + (team2_unit.size() - 1);
		obj->transform->SetLocalPos(teamBase2->transform->GetLocalPos());
	}*/

	//인덱스 설정 - Team1
	if (ZERO_INPUT_MGR->GetKeyState('1') == KEY_DOWN) {
		team1_currentIndex = 0;
		createUnit_1 = true;
	}
	if (ZERO_INPUT_MGR->GetKeyState('2') == KEY_DOWN) {
		team1_currentIndex = 1;
		createUnit_1 = true;
	}
	if (ZERO_INPUT_MGR->GetKeyState('3') == KEY_DOWN) {
		team1_currentIndex = 2;
		createUnit_1 = true;
	}
	if (ZERO_INPUT_MGR->GetKeyState('4') == KEY_DOWN) {
		team1_currentIndex = 3;
		createUnit_1 = true;
	}
	if (ZERO_INPUT_MGR->GetKeyState('5') == KEY_DOWN) {
		team1_currentIndex = 4;
		createUnit_1 = true;
	}
	if (ZERO_INPUT_MGR->GetKeyState('6') == KEY_DOWN) {
		team1_currentIndex = 5;
		createUnit_1 = true;
	}
	if (ZERO_INPUT_MGR->GetKeyState('W') == KEY_DOWN) {
		if (team1_currentIndex == 3)
			team1_currentIndex = 0;
		if (team1_currentIndex == 4)
			team1_currentIndex = 1;
		if (team1_currentIndex == 5)
			team1_currentIndex = 2;
	}
	if (ZERO_INPUT_MGR->GetKeyState('A') == KEY_DOWN) {
		if (0 < team1_currentIndex)
			team1_currentIndex--;
		else if (team1_currentIndex == 0)
			team1_currentIndex = 5;
	}
	if (ZERO_INPUT_MGR->GetKeyState('D') == KEY_DOWN) {
		if (team1_currentIndex < 5)
			team1_currentIndex++;
		else if (team1_currentIndex == 5)
			team1_currentIndex = 0;
	}
	if (ZERO_INPUT_MGR->GetKeyState('S') == KEY_DOWN) {
		if (team1_currentIndex == 0)
			team1_currentIndex = 3;
		if (team1_currentIndex == 1)
			team1_currentIndex = 4;
		if (team1_currentIndex == 2)
			team1_currentIndex = 5;
	}
	if (ZERO_INPUT_MGR->GetKeyState(' ') == KEY_DOWN) {
		createUnit_1 = true;
	}

	//인덱스 설정 - Team2
	if (ZERO_INPUT_MGR->GetKeyState('U') == KEY_DOWN){
		team2_currentIndex = 2;
		createUnit_2 = true;
	}
	if (ZERO_INPUT_MGR->GetKeyState('I') == KEY_DOWN) {
		team2_currentIndex = 1;
		createUnit_2 = true;
	}
	if (ZERO_INPUT_MGR->GetKeyState('O') == KEY_DOWN) {
		team2_currentIndex = 0;
		createUnit_2 = true;
	}
	if (ZERO_INPUT_MGR->GetKeyState('J') == KEY_DOWN) {
		team2_currentIndex = 5;
		createUnit_2 = true;
	}
	if (ZERO_INPUT_MGR->GetKeyState('K') == KEY_DOWN) {
		team2_currentIndex = 4;
		createUnit_2 = true;
	}
	if (ZERO_INPUT_MGR->GetKeyState('L') == KEY_DOWN) {
		team2_currentIndex = 3;
		createUnit_2 = true;
	}

	if (ZERO_INPUT_MGR->GetKeyState(VK_UP) == KEY_DOWN) {
		if (team2_currentIndex == 3)
			team2_currentIndex = 0;
		else if (team2_currentIndex == 4)
			team2_currentIndex = 1;
		else if (team2_currentIndex == 5)
			team2_currentIndex = 2;
	}
	if (ZERO_INPUT_MGR->GetKeyState(VK_RIGHT) == KEY_DOWN) {
		if (0 < team2_currentIndex)
			team2_currentIndex--;
		else if (team2_currentIndex == 0)
			team2_currentIndex = 5;
	}
	if (ZERO_INPUT_MGR->GetKeyState(VK_LEFT) == KEY_DOWN) {
		if (team2_currentIndex < 5)
			team2_currentIndex++;
		else if (team2_currentIndex == 5)
			team2_currentIndex = 0;
	}
	if (ZERO_INPUT_MGR->GetKeyState(VK_DOWN) == KEY_DOWN) {
		if (team2_currentIndex == 0)
			team2_currentIndex = 3;
		else if (team2_currentIndex == 1)
			team2_currentIndex = 4;
		else if (team2_currentIndex == 2)
			team2_currentIndex = 5;
	}
	if (ZERO_INPUT_MGR->GetKeyState(VK_RETURN) == KEY_DOWN) {
		createUnit_2 = true;
	}

	if (createDelay_1 > 0.5f) {
		if(createUnit_1)
			CreateUnit(Team::TEAM_1);

		createUnit_1 = false;
	}
	if(createDelay_2 > 0.5f) {
		if(createUnit_2)
			CreateUnit(Team::TEAM_2);

		createUnit_2 = false;
	}

	
}

void TeamManager::LateUpdate()
{
	Component::LateUpdate();

	//Check Collision
	CheckDeathUnit();

	//Show Result
	if (baseHp_1 <= 0.0f) {
		auto iter = new ResultScene();
		iter->winTeam = Team::TEAM_2;
		ZERO_SCENE_MGR->ChangeScene(iter);
	}
	else if(baseHp_2 <= 0.0f) {
		auto iter = new ResultScene();
		iter->winTeam = Team::TEAM_1;
		ZERO_SCENE_MGR->ChangeScene(iter);
	}
}

void TeamManager::CheckDeathUnit()
{
	//bullet과 unit 충돌 체크
	for (GameObject* bullet : bullet_unit) {
		BulletMovement* bm = bullet->GetComponent<BulletMovement>();
		
		if (!bm->GetIsStarted()) continue;

		if (bm->team == Team::TEAM_1) {
			for (GameObject* team : team2_unit) {
				if (bm->tr->GetLocalPos().x
					+ bullet->GetComponent<Sprite2DRenderer>()->GetTextureSize().x > team->transform->GetLocalPos().x && bm->tr->GetLocalPos().x < team->transform->GetLocalPos().x) {
					team->GetComponent<UnitMovement>()->GetDamage(bm->damage);
					GameObject::Destroy(bullet);
					break;
				}
			}

			if (bm->tr->GetLocalPos().x
				+ bullet->GetComponent<Sprite2DRenderer>()->GetTextureSize().x > teamBase2->transform->GetLocalPos().x) {
				GameObject::Destroy(bullet);
				baseHp_2 -= bm->damage;
			}
		}
		if (bm->team == Team::TEAM_2) {
			for (GameObject* team : team1_unit) {
				if (bm->tr->GetLocalPos().x
					- bullet->GetComponent<Sprite2DRenderer>()->GetTextureSize().x < team->transform->GetLocalPos().x && bm->tr->GetLocalPos().x > team->transform->GetLocalPos().x) {
					team->GetComponent<UnitMovement>()->GetDamage(bm->damage);
					GameObject::Destroy(bullet);
					break;
				}
			}

			if (bm->tr->GetLocalPos().x
				- bullet->GetComponent<Sprite2DRenderer>()->GetTextureSize().x < teamBase1->transform->GetLocalPos().x) {
				GameObject::Destroy(bullet);
				baseHp_1 -= bm->damage;
			}
		}
	}

	// 리스트 유닛 처리
	team1_unit.erase(std::remove_if(team1_unit.begin(), team1_unit.end(), [&](auto iter) {
		bool remove = iter->GetComponent<UnitMovement>()->GetHp() <= 0.0f;
		if (remove) {
			GameObject::Destroy(iter);
		}
		return remove;
		}), team1_unit.end());

	team2_unit.erase(std::remove_if(team2_unit.begin(), team2_unit.end(), [&](auto iter) {
		bool remove = iter->GetComponent<UnitMovement>()->GetHp() <= 0.0f;
		if (remove) {
			GameObject::Destroy(iter);
		}
		return remove;
		}), team2_unit.end());

	bullet_unit.erase(std::remove_if(bullet_unit.begin(), bullet_unit.end(), [&](GameObject* iter) {
		return iter->GetIsDestroy();
		}), bullet_unit.end());

	if (baseHp_1 <= 0.0f) {
		baseHp_1 = 0.0f;
	}
	else if (baseHp_2 <= 0.0f) {
		baseHp_2 = 0.0f;
	}

	teamHp_1->GetComponent<UIHp>()->SetVisibleRect(Rect(65 * baseHp_1 / (defaultHp * (level_1 + 1)), 13));
	teamHp_2->GetComponent<UIHp>()->SetVisibleRect(Rect(65 * baseHp_2 / (defaultHp * (level_2 + 1)), 13));
}

void TeamManager::CreateUnit(Team team)
{
	if (team == Team::TEAM_1) {
		UnitType createType = (UnitType)0;
		createType = indexArr1[team1_currentIndex];

		if (money_1 - cost[(int)createType] >= 0.0f) {
			//돈 확인 후 생성(cost)
			money_1 -= cost[(int)createType];

			UnitBaseObject* obj = new UnitBaseObject();
			obj->GetComponent<UnitMovement>()->InitType(team, createType);
			team1_unit.push_back(obj);
			obj->transform->SetLocalPos(teamBase1->transform->GetLocalPos() + Vec2(30, 20.0f + Random(0.0f, 40.0f)));
			createDelay_1 = 0.0f;
		}	

		createUnit_1 = false;
	}

	if (team == Team::TEAM_2) {
		UnitType createType = (UnitType)0;
		createType = indexArr2[team2_currentIndex];

		if (money_2 - cost[(int)createType] >= 0.0f) {
			//돈 확인 후 생성(cost)
			money_2 -= cost[(int)createType];

			//createType의 돈 확인 후 생성(cost)
			UnitBaseObject* obj = new UnitBaseObject();
			obj->GetComponent<UnitMovement>()->InitType(team, createType);
			team2_unit.push_back(obj);
			obj->transform->SetLocalPos(teamBase2->transform->GetLocalPos() + Vec2(-30, 20.0f + Random(0.0f, 40.0f)));
			createDelay_2 = 0.0f;
		}

		createUnit_2 = false;
	}
}

void TeamManager::SetUnitIndex(UnitType* arr1, UnitType* arr2)
{
	for (int i = 0; i < 3; i++)
	{
		indexArr1[i + 3] = *(arr1 + i);
		indexArr2[i + 3] = *(arr2 + i);
	}
}

void TeamManager::CreateBullet(Team team, float damage, Vec2 pos)
{
	GameObject* obj = new Bullet();
	obj->GetComponent<BulletMovement>()->InitBullet(team, BulletType::ARROW, damage);
	obj->transform->SetLocalPos(pos);
	bullet_unit.push_back(obj);
}
