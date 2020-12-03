#pragma once
#include "Component.h"
class UIText :
    public Component
{
public:
    UIText();
    ~UIText();

    void Render() override;

    UIText* SetText(std::string text);
    UIText* SetSize(int size) { this->size = size; return this; }
    UIText* SetColor(D3DXCOLOR color) { this->color = color; return this; }
    UIText* SetFont(std::string fontName);

    LPD3DXFONT GetFont() { return font; }
    std::string GetText() { return text; }
    int GetSize() { return size; }
    D3DXCOLOR GetColor() { return color; }
private:
    LPD3DXFONT font;
    std::string text;
    int size;
    D3DXCOLOR color;
    Rect visibleRect;
};

