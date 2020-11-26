#include "stdafx.h"
#include "Button.h"
#include "ZeroSystem.h"
#include "ZeroMath.h"
#include "GameObject.h"
#include "Transform.h"
#include "Sprite2DRenderer.h"

Button::~Button() {
}
void Button::Start() {
    Component::Start();
}
void Button::Update() {
    Component::Update();

    Vec2 currentCursorPos = ZERO_INPUT_MGR->GetCursorPos();

    if (boundaryRect.Offset(GetOwner()->transform->GetLocalPos()).Contain(currentCursorPos)) {
        isOnCursor = true;
        isEndCursor = true;
    }
    else {
        isOnCursor = false;
        isEndCursor = false;
    }

    if (isOnCursor) {
        if (ZERO_INPUT_MGR->GetKeyState(VK_LBUTTON) == KEY_UP)
            isOnClick = true;
        else
            isOnClick = false;
    }

    if (isOnClick) {
        onClick();
    }

    if (isEnableAnimation) {
        if (isOnCursor) {
            GetOwner()->transform->SetScale(
                Lerp(GetOwner()->transform->GetScale(),
                    upScale,
                    upSpeed * ZERO_TIME_MGR->GetDeltaTime()));
        }
        else {
            GetOwner()->transform->SetScale(
                Lerp(GetOwner()->transform->GetScale(),
                    defScale,
                    upSpeed * ZERO_TIME_MGR->GetDeltaTime()));

        }
    }
}
void Button::SetTextureImage(const char* path) {
    Sprite2DRenderer* renderer = GetOwner()->GetComponent<Sprite2DRenderer>();
    renderer->SetTexture(path);

    boundaryRect = Rect(0, 0, renderer->GetWidth(), renderer->GetHeight());
    GetOwner()->transform->SetScaleCenter(Vec2(renderer->GetWidth() / 2, renderer->GetHeight() / 2));
    GetOwner()->transform->SetRotationCenter(Vec2(renderer->GetWidth() / 2, renderer->GetHeight() / 2));
}