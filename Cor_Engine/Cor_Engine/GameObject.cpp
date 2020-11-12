#include "stdafx.h"
#include "GameObject.h"

void GameObject::Init()
{
	Entity::Init();

	transform = AddComponent<Transform>();
}
