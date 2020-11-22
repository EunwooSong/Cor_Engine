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

void BoxCollider::Update() {
    Component::Update();
}