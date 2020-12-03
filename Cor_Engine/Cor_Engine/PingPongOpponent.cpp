#include "stdafx.h"
#include "PingPongOpponent.h"
#include "Transform.h"
#include "BoxCollider.h"


PingPongOpponent::PingPongOpponent() = default;

PingPongOpponent::~PingPongOpponent() = default;

void PingPongOpponent::SetValue(GameObject* ball) {
	this->ball = ball;
}

void PingPongOpponent::Update()
{
	auto c = this->ball->GetComponent<BoxCollider>();
	auto ballValue = this->ball->transform->GetLocalPos();
	this->GetOwner()->transform->SetLocalPos(
		this->GetOwner()->transform->GetLocalPos().x,
		ballValue.y - 50
	);
}


