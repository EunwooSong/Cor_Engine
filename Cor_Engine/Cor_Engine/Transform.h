#pragma once
#include "Component.h"
class Transform :
    public Component
{
public:
    Transform() :
        localPos(0, 0),
        worldPos(0, 0),
        scaleCenter(0, 0),
        scale(1, 1),
        rotationCenter(0, 0),
        rotation(0),
        parent(nullptr) {};
    ~Transform() {};

    void Start() override;
    void Update() override;
    void Render() override;
    void LateUpdate() override;
    void EndScene() override;
    void UpdateTransformation();
    
    Vec2 GetLocalPos() { return localPos; }
    Vec2 GetWorldPos() { return worldPos; }
    float GetRotation() { return rotation; }
    Vec2 GetScale() { return scale; }
    Transform* GetChild(int index) { return children[index]; }
    Transform* GetParent() { return parent; }
    const D3DXMATRIX& GetMatrix() { return mat; }

    void SetParent(Transform* iter)     { parent = iter; };
    void SetLocalPos(Vec2 localPos)     { this->localPos = localPos; };
    void SetRotation(float z)           { this->rotation = z; }
    void SetRotationCenter(Vec2 rc)     { rotationCenter = rc; }
    void SetScale(Vec2 scale)           { this->scale = scale; }
    void SetScaleCenter(Vec2 sc)        { scaleCenter = sc; }
    void SetIsUiObject(bool isUiObject) { this->isUiObject = isUiObject; }
    
    void Translate(Vec2 pos) { localPos += pos; }
    void AddChild(Transform* iter);
    void PopChild(Transform* iter);
    void MulMatrix(D3DXMATRIX mat) { if(!isUiObject) this->mat *= mat; }

private:
    //Position, Direction, Angles, Quaternion, scale, matrix
    Vec2 localPos;
    Vec2 worldPos;      //ReadOnly
    Vec2 scaleCenter;
    Vec2 scale;
    Vec2 rotationCenter;
    float rotation;
    D3DXMATRIX mat;

    bool isUiObject;

    Transform* parent;
    std::vector<Transform*> children;
};

