#include "stdafx.h"
#include "WindowsApplication.h"
#include <string>

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

    hWnd = CreateWindow(
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
    );

    ShowWindow(hWnd, 10);
    return hWnd;
}
void WindowsApplication::Initialize() {
    ZeroMemory(&hInstance, sizeof(hInstance));
    hInstance = GetModuleHandle(NULL);
    
    wchar_t buffer[50];
    mbstowcs(buffer, appName.c_str(),appName.size() + 1);

    WNDCLASSEX wndClass = {
        sizeof(WNDCLASSEX),
        CS_CLASSDC,
        WndProc, 0L, 0L,
        GetModuleHandle(NULL),
        NULL,
        NULL,
        NULL,
        NULL,
        buffer,
        NULL };

    RegisterClassEx(&wndClass);
}
void WindowsApplication::RegisterInfo(std::string app_name, int w, int h, bool ifs)
{
    appName = app_name; windowHeight = h; windowWidth = w; isFullScreen = ifs;
}
WindowsApplication* WindowsApplication::Instance() {
    static WindowsApplication* iter = new WindowsApplication();
    return iter;
}
MSG WindowsApplication::CheckMessage() {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg;
}