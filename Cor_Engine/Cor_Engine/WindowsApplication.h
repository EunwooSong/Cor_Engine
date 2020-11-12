#pragma once
#include <Windows.h>
#include <string>

#define WINDOWS_APPLICATION WindowsApplication::Instance()

class WindowsApplication {
public:
    WindowsApplication() :
        hWnd(nullptr),
        hInstance(nullptr),
        appName("ZeroApplication"),
        windowWidth(1280), 
        windowHeight(720),
        msg({0,}),
        isFullScreen(false) {}

    ~WindowsApplication() {}

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
    HWND FloatWindow(int cmdShow);

    void Initialize();
    void RegisterInfo(std::string app_name, int w, int h, bool ifs = false);
    MSG CheckMessage();

    static WindowsApplication* Instance();

    HWND GetHWND() { return hWnd; }
    HINSTANCE GetHINSTANCE() { return hInstance; }

private:
    HWND hWnd;
    HINSTANCE hInstance;
    MSG msg;
   
    std::string appName;
    int windowWidth;
    int windowHeight;
    bool isFullScreen;
};