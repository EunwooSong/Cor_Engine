#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "stdafx.h"

#define DIRECTX_CORE DirectXCore::Instance()

class DirectXCore {
public:
    static std::unique_ptr<DirectXCore> instance;
    static std::once_flag onlyOnce;

    DirectXCore() = default;
    ~DirectXCore();

    void Initialize(HWND hWnd);
    void Release();

    void BeginRender();
    void EndRender();

    void RegisterInfo(int, int, bool ifs = false);

    static DirectXCore* Instance();

    LPDIRECT3D9& GetDirect3D()              { return p_d3d; }
    D3DPRESENT_PARAMETERS& GetD3DParams()   { return p_d3d_params; }
    LPDIRECT3DDEVICE9& GetDirect3DDevice()  { return p_d3d_device; }
    LPD3DXSPRITE& GetSprite()               { return p_d3d_sprite; }
    LPD3DXLINE& GetLine()                   { return p_d3d_line; }
    LPD3DXEFFECT& GetD3DEffect()            { return p_d3d_effect; }

private:
    LPDIRECT3D9             p_d3d;
    D3DPRESENT_PARAMETERS   p_d3d_params;
    LPDIRECT3DDEVICE9       p_d3d_device;
    LPD3DXSPRITE            p_d3d_sprite;
    LPD3DXLINE              p_d3d_line;
    LPD3DXEFFECT            p_d3d_effect;

    int windowWidth;
    int windowHeight;
    bool isFullScreen;
};

