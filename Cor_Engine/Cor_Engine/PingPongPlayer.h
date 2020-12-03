#pragma once
#include "Component.h"
#include "RigidBody2D.h"
#include "GameObject.h"

class PingPongPlayer : public Component
{
public:
	PingPongPlayer();
	~PingPongPlayer();

	void Start() override;
	void Update() override;
};

