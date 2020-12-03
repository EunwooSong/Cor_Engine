#pragma once
#include "Component.h"

class BoxCollider : public Component {
public:
    BoxCollider() = default;
    ~BoxCollider() = default;
    BoxCollider(Vec2 centerPos, Vec2 scale, double rotate);

    Vec2 GetLeftTopPos();

    Vec2 GetRightBottomPos();

    Vec2 GetCenterPos();

    Vec2 GetScaleValue();

    double GetLeftPos();
    double GetRightPos();
    double GetTopPos();
    double GetBottomPos();

    double GetRotation() const { return this->rotation; }

    bool GetIsCollided() const { return this->isCollided; }

    bool GetIsTrigger() const { return this->isTrigger; }

    bool GetIsPreviousLoopCollisionResolved() const { return this->isPreviousLoopCollisionResolved; }

    void SetRelativePos(Vec2 lt, Vec2 rb, double rot = 0);

    void SetAbsolutePos(Vec2 centerPos, Vec2 scale, double rotate = 0);

    void SetCenterPos(Vec2 v) { this->centerPos = v; }

    void SetSceleValue(Vec2 v) { this->scaleValue = v; }

    void SetRotation(double r) { this->rotation = r; }

    void SetIsCollided(bool b) { this->isCollided = b; }

    void SetIsTrigger(bool b) { this->isTrigger = b; }

    void SetIsPreviousLoopCollisionResolved(bool b) { this->isPreviousLoopCollisionResolved = b; }

    void Start() override;
    void Update() override;

private:
    Vec2 centerPos{};
    Vec2 scaleValue{};
    double rotation = 0.0;
    bool isCollided = false;
    bool isTrigger = false;
    bool isPreviousLoopCollisionResolved = false;
};
