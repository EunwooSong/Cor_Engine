#include "stdafx.h"
#include "BoxCollider.h"
#include "Transform.h"
#include "GameObject.h"

Vec2 BoxCollider::GetLeftTopPos() {
    Transform* transform = GetOwner()->GetComponent<Transform>();
    return transform->GetWorldPos();
}
Vec2 BoxCollider::GetRightBottomPos() {
    Transform* transform = GetOwner()->GetComponent<Transform>();
    return this->relativeRightBottomPos - this->relativeLeftTopPos + transform->GetWorldPos();
}

Vec2 BoxCollider::GetCenterPos() {
    Transform* transform = GetOwner()->GetComponent<Transform>();
    return this->relativeLeftTopPos + GetSize() / 2;
}

Vec2 BoxCollider::GetSize() {
    Transform* transform = GetOwner()->GetComponent<Transform>();
    return this->relativeRightBottomPos - this->relativeLeftTopPos;
    
}

void BoxCollider::Update() {
    Component::Update();
}