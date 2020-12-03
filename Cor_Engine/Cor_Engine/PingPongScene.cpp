#include "stdafx.h"
#include "PingPongScene.h"
#include "GameObject.h"
#include "Sprite2DRenderer.h"
#include "RigidBody2D.h"
#include "BoxCollider.h"
#include "Transform.h"

constexpr double multiplyValue = 1.2;

PingPongScene::PingPongScene() = default;

PingPongScene::~PingPongScene() = default;

struct G_Walls {
	GameObject* left;
	GameObject* right;
	GameObject* top;
	GameObject* bottom;
	G_Walls() {
		this->left = new GameObject();
		this->right = new GameObject();
		this->top = new GameObject();
		this->bottom = new GameObject();

		this->left->AddComponent<BoxCollider>()->SetIsTrigger(true);
		this->right->AddComponent<BoxCollider>()->SetIsTrigger(true);
		this->top->AddComponent<BoxCollider>();
		this->bottom->AddComponent<BoxCollider>();
		
		this->top->AddComponent<RigidBody2D>();
		this->bottom->AddComponent<RigidBody2D>();
	}
};

struct G_Obj {
	GameObject* object;
	RigidBody2D* rigidBody;
	BoxCollider* collider;
	Sprite2DRenderer* renderer;
	
	G_Obj(int) {
		this->object = new GameObject();
		this->collider = this->object->AddComponent<BoxCollider>();
		this->rigidBody = this->object->AddComponent<RigidBody2D>();
		this->renderer = this->object->AddComponent<Sprite2DRenderer>();
	}
};

void PingPongScene::Init()
{
	Scene::Init();

	G_Obj* player = new G_Obj(0);
	player->object->transform->SetLocalPos(10.0, 10.0);
	player->object->transform->SetScale(10, 100);
	player->renderer->SetTexture("Resources/Character/player.png");
	
	G_Obj* opponent = new G_Obj(0);
	opponent->object->transform->SetLocalPos(10.0, 10.0);
	opponent->object->transform->SetScale(1280 - 10, 100);
	opponent->renderer->SetTexture("Resources/Character/player.png");

	G_Obj* ball = new G_Obj(0);
	ball->rigidBody->SetVelocity(-40.0, 40.0);
	ball->rigidBody->SetRestitution(0);
	ball->object->transform->SetLocalPos(1280 / 2, 720 / 2);
	ball->object->transform->SetScale(20, 20);
	ball->renderer->SetTexture("Resources/Character/ball.png");

	G_Walls* walls = new G_Walls();


}
