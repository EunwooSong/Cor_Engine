#include "stdafx.h"
#include "InputManager.h"
#include "Zero_System.h"

void InputManager::Update()
{
    for (int i = 0; i < 256; i++) {
        lastKeys[i] = currentKeys[i];
        currentKeys[i] = ::GetKeyState(i) & 0x8000;
    }

    GetCursorPos(&cursorPos);
    ScreenToClient(ZERO_ENGINE->GetHWND(), &cursorPos);
}
