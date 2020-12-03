#include "stdafx.h"
#include "UnitBaseObject.h"
#include "UnitMovement.h"
#include "AnimationController.h"
#include "TeamManager.h"
#include "Transform.h"
#include "Sprite2DRenderer.h"
#include "RigidBody2D.h"
#include "BoxCollider.h"
#include "CLogger.h"

void UnitBaseObject::Init()
{
	AddComponent<UnitMovement>();
	AddComponent<Sprite2DRenderer>();
	AddComponent<AnimationController>();
	AddComponent<RigidBody2D>()->setIsStrict(true);
	AddComponent<BoxCollider>();
	
}