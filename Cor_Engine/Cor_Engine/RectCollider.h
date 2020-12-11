#pragma once
#include "Component.h"
class RectCollider :
    public Component
{
public:
    RectCollider() : rect(0, 0, 0, 0) {};
    ~RectCollider() = default;

    void SetRect(Rect rect) { this->rect = rect; }

    Rect GetRect() { return rect; }
    Rect GetRectWithPos();

private:
    Rect rect;
};