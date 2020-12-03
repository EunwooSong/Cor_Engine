#include "stdafx.h"
#include "PingPongScene.h"
#include "GameObject.h"
#include "Sprite2DRenderer.h"
#include "RigidBody2D.h"
#include "BoxCollider.h"
#include "Transform.h"
#include "PingPongPlayer.h"
#include "PingPongOpponent.h"

constexpr double multiplyValue = 1.01;

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

		this->top->AddComponent<RigidBody2D>()->SetIsStrict(true)->SetGravity(0);
		this->bottom->AddComponent<RigidBody2D>()->SetIsStrict(true)->SetGravity(0);
		this->left->AddComponent<RigidBody2D>()->SetIsStrict(true)->SetGravity(0);
		this->right->AddComponent<RigidBody2D>()->SetIsStrict(true)->SetGravity(0);

		this->top->AddComponent<BoxCollider>();
		this->bottom->AddComponent<BoxCollider>();
		this->left->AddComponent<BoxCollider>();
		this->right->AddComponent<BoxCollider>();

		this->top->AddComponent<Sprite2DRenderer>()->SetTexture("Resources/Stage/wall-x.png");
		this->bottom->AddComponent<Sprite2DRenderer>()->SetTexture("Resources/Stage/wall-x.png");		
		this->left->AddComponent<Sprite2DRenderer>()->SetTexture("Resources/Stage/wall-y.png");
		this->right->AddComponent<Sprite2DRenderer>()->SetTexture("Resources/Stage/wall-y.png");

		this->top->transform->SetLocalPos(0, 0);
		this->bottom->transform->SetLocalPos(0, (double)720 - 10);
		this->left->transform->SetLocalPos(0, 10);
		this->right->transform->SetLocalPos(1270, 10);
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
		this->rigidBody = this->object->AddComponent<RigidBody2D>()->SetGravity(0);
		this->renderer = this->object->AddComponent<Sprite2DRenderer>();
	}
};

void PingPongScene::Init()
{
	Scene::Init();

	Scene::RegisterComponent<PingPongPlayer>();
	Scene::RegisterComponent<PingPongOpponent>();


	G_Obj* ball = new G_Obj(0);
	ball->rigidBody->SetVelocity(-80.0 * 2, -60.0 * 2);
	//ball->rigidBody->SetRestitution(0);
	ball->object->transform->SetLocalPos(1280 / 2, 720 / 2);
	ball->renderer->SetTexture("Resources/Character/ball.png");


	G_Obj* player = new G_Obj(0);
	player->object->transform->SetLocalPos(10.0, 15.0);
	player->rigidBody->SetRestitution(multiplyValue);
	player->renderer->SetTexture("Resources/Character/player.png");
	player->rigidBody->SetIsStrict(true);
	player->object->AddComponent<PingPongPlayer>();

	
	G_Obj* opponent = new G_Obj(0);
	opponent->object->transform->SetLocalPos(1260.0, 15.0);
	opponent->rigidBody->SetRestitution(multiplyValue);
	opponent->renderer->SetTexture("Resources/Character/player.png");
	opponent->rigidBody->SetIsStrict(true);
	opponent->object->AddComponent<PingPongOpponent>()->SetValue(ball->object);

	G_Walls* walls = new G_Walls();
}

//void PingPongScene::
