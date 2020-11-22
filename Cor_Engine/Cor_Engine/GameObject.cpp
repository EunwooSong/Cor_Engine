#include "stdafx.h"
#include "GameObject.h"
#include "Transform.h"

void GameObject::Init()
{
	transform = AddComponent<Transform>();
}
