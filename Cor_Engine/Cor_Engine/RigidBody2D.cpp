#include "stdafx.h"
#include "RigidBody2D.h"
#include "ZeroSystem.h"
#include "BoxCollider.h"
#include "Component.h"
#include "GameObject.h"
#include "Transform.h"

void RigidBody2D::LateUpdate() {
    auto deltaTime = ZERO_TIME_MGR->GetDeltaTime();

    Vec2 vel{ 0, 0 };

    vel.y += deltaTime * GetGravity();

    AddVelocity(vel);

    GetOwner()->transform->Translate(Vec2(deltaTime * GetVelocity().x, deltaTime * GetVelocity().y));
}

float RigidBody2D::GetGravity() {
    if (GetOwner()->GetComponent<BoxCollider>()->GetIsCollided()) {
        return 0.0f;
    }

    return gravity;
}