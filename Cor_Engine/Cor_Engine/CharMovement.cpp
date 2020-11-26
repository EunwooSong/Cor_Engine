#include "stdafx.h"
#include "CharMovement.h"
#include "ZeroSystem.h"
#include "GameObject.h"
#include "Transform.h"

void CharMovement::Update()
{
	time += rand() % 10;
	GetOwner()->transform->Translate(Vec2(sin(time * 2), cos(time * 2)) * 300 * ZERO_TIME_MGR->GetDeltaTime());
}
