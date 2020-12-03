#include "stdafx.h"
#include "PingPongPlayer.h"
#include "ZeroSystem.h"
#include "InputManager.h"
#include "RigidBody2D.h"
#include "Transform.h"
#include <Windows.h>

constexpr double moveSpeed = 300.0;

PingPongPlayer::PingPongPlayer() = default;

PingPongPlayer::~PingPongPlayer() = default;

void PingPongPlayer::Start() {
	Component::Start();

}

void PingPongPlayer::Update() {
	Component::Update();

	auto upState = ZERO_INPUT_MGR->GetKeyState(VK_UP);
	auto downState = ZERO_INPUT_MGR->GetKeyState(VK_DOWN);

	short direction = 0;

	if (upState == KEY_PRESS) {
		if (downState == KEY_PRESS) {
			return;
		}

		direction = -1;
	}
	else if (downState == KEY_PRESS) {
		direction = 1;
	}
	auto r = this->GetOwner()->GetComponent<RigidBody2D>();
	auto t = this->GetOwner()->transform;

	t->SetLocalPos(
		t->GetLocalPos().x,
		t->GetLocalPos().y +
		moveSpeed * ZERO_TIME_MGR->GetDeltaTime() * direction);

}


