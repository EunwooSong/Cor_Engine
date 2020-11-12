#pragma once
#include "stdafx.h"

class Entity;
class GameObject;
class Component;
class Scene;
class BoxCollider;
class Transform;
class Rigidbody2D;

typedef struct Collision {
	GameObject* gameObject;
	Transform* transform;
} Collision;