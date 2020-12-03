#include "stdafx.h"
#include "UIText.h"
#include "ZeroSystem.h"
#include "GameObject.h"
#include "Transform.h"

UIText::UIText() : color(1,1,1,1), size(30)
{
	SetFont("¸¼Àº°íµñ");
	SetText("UIObject");
}

UIText::~UIText()
{
}

void UIText::Render()
{
	Component::Render();

	if (!isActive) return;
	ZERO_DIRECT3D->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
	ZERO_DIRECT3D->GetSprite()->SetTransform(&GetOwner()->transform->GetMatrix());
	font->DrawTextA(ZERO_DIRECT3D->GetSprite(), text.data(), -1, NULL, DT_TOP | DT_LEFT, color);
	ZERO_DIRECT3D->GetSprite()->End();
}

UIText* UIText::SetText(std::string text)
{
	this->text	= text;
	visibleRect = Rect(0, 0, (size / 2 - size / 10) * text.size(), size);
	return this;
}

UIText* UIText::SetFont(std::string fontName)
{
	D3DXCreateFontA(
		ZERO_DIRECT3D->GetDirect3DDevice(),
		size,
		size / 2 - size / 10,
		FW_HEAVY,
		D3DX_DEFAULT,
		NULL,
		DEFAULT_CHARSET,
		NULL,
		ANTIALIASED_QUALITY,
		NULL,
		fontName.c_str(),
		&font
	);

	return this;
}
