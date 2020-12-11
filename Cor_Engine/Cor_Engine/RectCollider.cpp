#include "stdafx.h"
#include "RectCollider.h"
#include "GameObject.h"
#include "Transform.h"

Rect RectCollider::GetRectWithPos()
{
    return rect.Offset(GetOwner()->transform->GetLocalPos());
}