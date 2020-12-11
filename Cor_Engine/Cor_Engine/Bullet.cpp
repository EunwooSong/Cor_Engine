#include "stdafx.h"
#include "Bullet.h"
#include "BulletMovement.h"
#include "RectCollider.h"

void Bullet::Init()
{
	AddComponent<BulletMovement>();
	AddComponent<RectCollider>();
}
