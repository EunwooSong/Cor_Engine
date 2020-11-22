#pragma once
#include "Component.h"
class Sprite2DRenderer
    : public Component {
public:
    Sprite2DRenderer() {}
    Sprite2DRenderer(const char* path);
    Sprite2DRenderer(std::string path);
    ~Sprite2DRenderer() {}

    void SetTexture(const char* path);


    void Render() override;

    int GetWidth() { return width; }
    int GetHeight() { return height; }

    Vec2 GetTextureSize() { return Vec2(width, height); }
    D3DXCOLOR GetColor() { return color; }
    Rect GetVisibleRect() { return visibleRect; }

    void SetColor(D3DXCOLOR color) { this->color = color; }
    void SetTexture(LPDIRECT3DTEXTURE9* texture);

protected:
    LPDIRECT3DTEXTURE9* texture;
    D3DXCOLOR color;
    Rect visibleRect;
    int width;
    int height;
};
