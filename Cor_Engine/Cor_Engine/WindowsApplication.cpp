#include "stdafx.h"
#include "WindowsApplication.h"
#include <string>
#include "Windows.h"

std::unique_ptr<WindowsApplication> WindowsApplication::instance;
std::once_flag WindowsApplication::onlyOnce;

WindowsApplication::~WindowsApplication()
{
}

LRESULT WindowsApplication::WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
    switch (iMessage)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
HWND WindowsApplication::FloatWindow(int cmdShow) {
    hInstance = GetModuleHandle(NULL);

    wchar_t app_buffer[50];
    mbstowcs(app_buffer, appName.c_str(), appName.size() + 1);

    /*hWnd = CreateWindow(
        TEXT("ZERO_ENGINE"),
        app_buffer,
        isFullScreen ? WS_EX_TOPMOST | WS_POPUP
        : WS_EX_TOPMOST | WS_OVERLAPPEDWINDOW,
        100, 0,
        windowWidth,
        windowHeight,
        GetDesktopWindow(),
        (HMENU)NULL,
        hInstance,
        NULL
    );*/

    hWnd = CreateWindow(L"ZeroEngine", app_buffer,
        WS_EX_TOPMOST | ((isFullScreen) ? WS_POPUP : WS_OVERLAPPEDWINDOW), 100, 0, windowWidth, windowHeight,
        GetDesktopWindow(), NULL, hInstance, NULL);
    ShowWindow(hWnd, SW_SHOWDEFAULT);
    return hWnd;
}
void WindowsApplication::Initialize() {
    ZeroMemory(&hInstance, sizeof(hInstance));
    hInstance = GetModuleHandle(NULL);

    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L,
        hInstance, NULL, NULL, NULL, NULL,
        L"ZeroEngine", NULL };
    RegisterClassEx(&wc);
}
void WindowsApplication::RegisterInfo(std::string app_name, int w, int h, bool ifs)
{
    appName = app_name; windowHeight = h; windowWidth = w; isFullScreen = ifs;
}
WindowsApplication* WindowsApplication::Instance() {
    static WindowsApplication iter;
    return &iter;
}
MSG WindowsApplication::CheckMessage() {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg;
}