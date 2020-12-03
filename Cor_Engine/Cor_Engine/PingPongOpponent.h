#pragma once
#include "Component.h"
#include "GameObject.h"

class PingPongOpponent : public Component
{
public:
	PingPongOpponent();
	~PingPongOpponent();
	void SetValue(GameObject* ball);
	void Update() override;
private:
	GameObject* ball;
};

