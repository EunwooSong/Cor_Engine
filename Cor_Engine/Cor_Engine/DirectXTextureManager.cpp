#include "stdafx.h"
#include "DirectXTextureManager.h"
#include "DirectXCore.h"

DirectXTextureManager::~DirectXTextureManager() {
}
LPDIRECT3DTEXTURE9* DirectXTextureManager::LoadTextureFormFile(const char* path) {
    if (textureMap[path] == NULL) {
        textureMap[path] = new LPDIRECT3DTEXTURE9();
        D3DXCreateTextureFromFileExA(
            DIRECTX_CORE->GetDirect3DDevice(),
            path,
            D3DX_DEFAULT_NONPOW2,
            D3DX_DEFAULT_NONPOW2,
            1,
            0,
            D3DFMT_UNKNOWN,
            D3DPOOL_MANAGED,
            D3DX_DEFAULT,
            D3DX_DEFAULT,
            NULL,
            NULL,
            NULL,
            *(&textureMap[path])
        );
    }

    return textureMap[path];
}
void DirectXTextureManager::Release() {
    for (auto iter : textureMap) {
        SAFE_RELEASE(*(iter.second));
        SAFE_DELETE(iter.second);
    }
}

