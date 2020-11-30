#include "stdafx.h"
#include "BoxCollider.h"
#include "Transform.h"
#include "GameObject.h"
#include "Scene.h"

BoxCollider::BoxCollider(Vec2 centerPos, Vec2 scale, double rotate) {
    this->centerPos = centerPos;
    this->scaleValue = scale;
    this->rotation = rotate;
}

Vec2 BoxCollider::GetLeftTopPos() {
    return centerPos - scaleValue;
}

Vec2 BoxCollider::GetRightBottomPos() {
    return centerPos + scaleValue;
}

Vec2 BoxCollider::GetCenterPos() {
    return this->centerPos;
}

Vec2 BoxCollider::GetScaleValue()
{
    return this->scaleValue;
}

void BoxCollider::SetRelativePos(Vec2 lt, Vec2 rb, double rot) {
    auto size = rb - lt;
    auto scale = size / 2;
    auto center = lt + scale;
    this->centerPos = center;
    this->scaleValue = scale;
    this->rotation = rot;
}

void BoxCollider::SetAbsolutePos(Vec2 centerPos, Vec2 scale, double rotate) {
    this->centerPos = centerPos;
    this->scaleValue = scale;
    this->rotation = rotate;
}

void BoxCollider::Start() {
    Component::Start();
    auto transform = GetOwner()->transform;
    this->SetRelativePos(transform->GetWorldPos(),
        transform->GetRightBottomPos(), transform->GetRotation());
    this->isMounted = true;
}

void BoxCollider::Update() {
    Component::Update();
    auto transform = GetOwner()->transform;
    this->SetRelativePos(transform->GetWorldPos(),
        transform->GetRightBottomPos(), transform->GetRotation());
}