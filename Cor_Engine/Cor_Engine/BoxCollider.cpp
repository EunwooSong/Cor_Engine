#include "stdafx.h"
#include "BoxCollider.h"
#include "Transform.h"
#include "GameObject.h"
#include "Scene.h"


constexpr double PI = 3.14159265358979;

double deg_to_rad(double deg) {
    return deg / 180 * PI;
}

double rad_to_deg(double rad) {
    return rad * 180 / PI;
}

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

double BoxCollider::GetLeftPos()
{
    return (double)this->centerPos.x - scaleValue.x;
}

double BoxCollider::GetRightPos()
{
    return (double)this->centerPos.x + scaleValue.x;
}

double BoxCollider::GetTopPos()
{
    return (double)this->centerPos.y - scaleValue.y;
}

double BoxCollider::GetBottomPos()
{
    return (double)this->centerPos.y + scaleValue.y;
}

void BoxCollider::SetRelativePos(Vec2 lt, Vec2 rb, double rot) {
    auto size = rb - lt;
    auto scale = size / 2;
    auto center = lt + scale;
    this->centerPos = center;
    this->scaleValue = scale;
    this->rotation = rad_to_deg(rot);
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
}

void BoxCollider::Update() {
    Component::Update();
    auto transform = GetOwner()->transform;
    this->SetRelativePos(transform->GetWorldPos(),
        transform->GetRightBottomPos(), transform->GetRotation());
}