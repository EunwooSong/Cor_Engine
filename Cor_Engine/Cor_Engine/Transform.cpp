#include "stdafx.h"
#include "Transform.h"

void Transform::Start() {
    Component::Start();
}
void Transform::Update() {
    Component::Update();
}
void Transform::Render() {
    Component::Render();

    if (!parent)
        UpdateTransformation();
}
void Transform::LateUpdate() {
    Component::LateUpdate();
}
void Transform::EndScene() {
    Component::EndScene();
}
void Transform::AddChild(Transform* iter) {
    iter->SetParent(this);
    children.push_back(iter);
}
void Transform::PopChild(Transform* iter) {
    children.erase(remove_if(children.begin(), children.end(), [&](auto i) {return i == iter; }), children.end());
}
void Transform::UpdateTransformation() {
    D3DXMatrixTransformation2D((D3DXMATRIX*)&mat, &scaleCenter, NULL, &scale, &rotationCenter, rotation, &localPos);

    worldPos = localPos;

    if (parent) {
        mat *= parent->mat;
        worldPos += parent->GetWorldPos();
    }

    if (children.size() > 0)
        for (auto& child : children)
            child->UpdateTransformation();
}