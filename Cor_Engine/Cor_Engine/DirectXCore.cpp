#include "stdafx.h"
#include "DirectXCore.h"

std::unique_ptr<DirectXCore> DirectXCore::instance;
std::once_flag DirectXCore::onlyOnce;

DirectXCore::~DirectXCore()
{
}

void DirectXCore::Initialize(HWND hWnd) {
    p_d3d = Direct3DCreate9(D3D_SDK_VERSION);
    ZeroMemory(&p_d3d_params, sizeof(p_d3d_params));

    p_d3d_params.BackBufferWidth = windowWidth;
    p_d3d_params.BackBufferHeight = windowHeight;
    p_d3d_params.Windowed = !isFullScreen;
    p_d3d_params.SwapEffect = D3DSWAPEFFECT_DISCARD;
    p_d3d_params.BackBufferFormat = D3DFMT_A8R8G8B8;

    p_d3d->CreateDevice(D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        hWnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &p_d3d_params,
        &p_d3d_device);

    D3DXCreateSprite(p_d3d_device, &p_d3d_sprite);
    D3DXCreateLine(p_d3d_device, &p_d3d_line);
}
void DirectXCore::Release() {
    SAFE_RELEASE(p_d3d_sprite);
    SAFE_RELEASE(p_d3d_device);
    SAFE_RELEASE(p_d3d);
}
void DirectXCore::BeginRender() {
    p_d3d_device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
    p_d3d_device->BeginScene();
}
void DirectXCore::EndRender() {
    p_d3d_sprite->End();

    p_d3d_device->EndScene();
    p_d3d_device->Present(NULL, NULL, NULL, NULL);
}

void DirectXCore::RegisterInfo(int w, int h, bool ifs)
{
    windowWidth = w; windowHeight = h;
    isFullScreen = ifs;
}

DirectXCore* DirectXCore::Instance() {
    static DirectXCore iter;
    return &iter;
}