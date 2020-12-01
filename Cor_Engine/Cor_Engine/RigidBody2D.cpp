#include "stdafx.h"
#include "RigidBody2D.h"
#include "ZeroSystem.h"
#include "BoxCollider.h"
#include "Component.h"
#include "GameObject.h"
#include "Transform.h"


void RigidBody2D::LateUpdate() {
    auto deltaTime = ZERO_TIME_MGR->GetDeltaTime();

    if (!this->strict) {
        Vec2 vel{ 0.0, 0.0 };

        vel.y += deltaTime * GetGravity();

        AddVelocity(vel);

        GetOwner()->transform->Translate(
            Vec2(deltaTime * GetVelocity().x, deltaTime * GetVelocity().y));
    }
    else {
        SetVelocity(Vec2(0.0, 0.0));
    }
}