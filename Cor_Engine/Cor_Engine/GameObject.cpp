#include "stdafx.h"
#include "GameObject.h"
#include "Transform.h"
#include "Scene.h"

void GameObject::Init()
{
	transform = AddComponent<Transform>();
}