#pragma once

#include <map>
#include <d3dx9.h>

class DirectXTextureManager {
private:
    std::map<const char*, LPDIRECT3DTEXTURE9*> textureMap;

public:
    DirectXTextureManager() {};
    ~DirectXTextureManager();
    void Release();


    LPDIRECT3DTEXTURE9* LoadTextureFormFile(const char* path);
};

