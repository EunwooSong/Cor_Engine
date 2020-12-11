#include "stdafx.h"
#include "GameScene.h"
#include "GameObject.h"
#include "TeamManager.h"
#include "UnitMovement.h"
#include "Transform.h"
#include "Sprite2DRenderer.h"
#include "UnitBaseObject.h"
#include "RigidBody2D.h"
#include "BoxCollider.h"
#include "RectCollider.h"
#include "BulletMovement.h"
#include "UserPickUIManager.h"
#include "UIImageRenderer.h"
#include "UIHp.h"
#include "UIText.h"

GameScene::GameScene() {
}

GameScene::~GameScene() {
}

void GameScene::Init() {
	Scene::Init();

	RegisterComponent<TeamManager>();
	RegisterComponent<UnitMovement>();
	RegisterComponent<RectCollider>();
	RegisterComponent<BulletMovement>();
	RegisterComponent<UserPickUIManager>();
	RegisterComponent<UIImageRenderer>();
	RegisterComponent<UIHp>();
	RegisterComponent<UIText>();

	GameObject* bg = new GameObject();
	bg->AddComponent<Sprite2DRenderer>()->SetTexture("Resources/Stage/stage_1.png");

	//������ġ1
	GameObject* base_1 = new GameObject();
	base_1->AddComponent<Sprite2DRenderer>()->SetTexture("Resources/UI/����/����1.png");
	base_1->transform->SetLocalPos(Vec2(0, 560));
	base_1->AddComponent<RectCollider>()->SetRect(base_1->GetComponent<Sprite2DRenderer>()->GetVisibleRect());

	//������ġ2
	GameObject* base_2 = new GameObject();
	base_2->AddComponent<Sprite2DRenderer>()->SetTexture("Resources/UI/����/����1.png");
	base_2->transform->SetLocalPos(Vec2(1280, 560));
	base_2->transform->SetScale(Vec2(-1.0f, 1.0f));
	base_2->AddComponent<RectCollider>()->SetRect(base_2->GetComponent<Sprite2DRenderer>()->GetVisibleRect());

	//�� �޴��� ���
	GameObject* teamManager = new GameObject();
	teamManager->SetName("TeamMgr");
	TeamManager* teamMGR = teamManager->AddComponent<TeamManager>();
	teamMGR->SetUnitIndex(arr[0], arr[1]);
	teamMGR->teamBase1 = base_1;
	teamMGR->teamBase2 = base_2;

	//�� �޴��� ������ UI �ְ� UIManager����
	GameObject* uiManager = new GameObject();
	auto mgr = uiManager->AddComponent<UserPickUIManager>();
	mgr->teamMGR = teamMGR;
	mgr->Init(teamMGR->indexArr1, teamMGR->indexArr2);

	//�׽�Ʈ Unit�߰�
	/*GameObject* testUnit = new GameObject();
	testUnit->AddComponent<Sprite2DRenderer>();
	testUnit->AddComponent<AnimationController>();
	testUnit->AddComponent<UnitMovement>();
	testUnit->AddComponent<BoxCollider>();
	testUnit->AddComponent<RigidBody2D>()->setIsStrict(true);*/


	/*testUnit->transform->SetLocalPos(base_1->transform->GetLocalPos());
	testUnit->GetComponent<Sprite2DRenderer>()->SetTexture("Resources/Character/Į��/Idle/0.png");
	AnimationController* testAnim = testUnit->GetComponent<AnimationController>();

	SpriteAnimation* anim_move = new SpriteAnimation();
	anim_move->SetFps(0.5);
	anim_move->AddTextures("Resources/Character/Į��/Walk", 2);

	SpriteAnimation* anim_attack = new SpriteAnimation();
	anim_attack->SetFps(0.5);
	anim_attack->AddTextures("Resources/Character/Į��/Attack", 2);

	testAnim->AddAnimationNode("Move", anim_move);
	testAnim->AddAnimationNode("Attack", anim_attack);
	testAnim->SetHasExitTime("Move", "Attack", true);
	testAnim->SetHasExitTime("Attack", "Move", true);
	testAnim->SetEntryAnimationNode("Move");*/
}