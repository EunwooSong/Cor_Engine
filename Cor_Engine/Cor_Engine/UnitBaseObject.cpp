#include "stdafx.h"
#include "UnitBaseObject.h"
#include "UnitMovement.h"
#include "AnimationController.h"
#include "TeamManager.h"
#include "Transform.h"
#include "Sprite2DRenderer.h"

void UnitBaseObject::Init()
{
	AddComponent<UnitMovement>();
	AddComponent<Sprite2DRenderer>();
	AddComponent<AnimationController>();
}
