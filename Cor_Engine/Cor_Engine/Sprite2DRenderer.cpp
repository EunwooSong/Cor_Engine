#include "stdafx.h"
#include "Sprite2DRenderer.h"
#include "Transform.h"
#include "ZeroSystem.h"

Sprite2DRenderer::Sprite2DRenderer(const char* path) {
    SetTexture(path);
}

Sprite2DRenderer::Sprite2DRenderer(std::string path) {
    SetTexture(path.c_str());
}

void Sprite2DRenderer::SetTexture(const char* path) {
    texture = ZERO_TEXTURE_MGR->LoadTextureFormFile(path);

    D3DSURFACE_DESC desc;
    (*texture)->GetLevelDesc(0, &desc);

    width = desc.Width;
    height = desc.Height;

    visibleRect = Rect(0, 0, width, height);

    color = D3DCOLOR_ARGB(255, 255, 255, 255);
}

void Sprite2DRenderer::Render() {
    Component::Render();
    Transform* transform = m_Owner->GetScene()->GetComponent<Transform>(m_Owner->GetEntityID());
    ZERO_DIRECT3D->GetSprite()->SetTransform(&transform->GetMatrix());
    ZERO_DIRECT3D->GetSprite()->Draw(*texture, &visibleRect, NULL, NULL, color);
}

void Sprite2DRenderer::SetTexture(LPDIRECT3DTEXTURE9* texture)
{
    this->texture = texture;

    D3DSURFACE_DESC desc;
    (*texture)->GetLevelDesc(0, &desc);

    width = desc.Width;
    height = desc.Height;

    visibleRect = Rect(0, 0, width, height);

    color = D3DCOLOR_ARGB(255, 255, 255, 255);
}