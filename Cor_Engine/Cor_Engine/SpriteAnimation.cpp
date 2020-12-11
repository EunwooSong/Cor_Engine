#include "stdafx.h"
#include "SpriteAnimation.h"
#include "ZeroSystem.h"

void SpriteAnimation::Update() {
    currentFrame += ZERO_TIME_MGR->GetDeltaTime() * fps;

    if (isLoopEnd)
        isLoopEnd = false;

    if ((int)currentFrame >= textureCount) {
        if (isLoop) {
            isLoopEnd = true;
            currentFrame = 0;
        }
        else {
            currentFrame = textureCount - 1;
            isEnd = true;
        }
    }
}
void SpriteAnimation::AddTextures(std::string root, int textureCount) {
    this->textureCount = textureCount;
    for (int i = 0; i < textureCount; i++) {
        textures.push_back(ZERO_TEXTURE_MGR->LoadTextureFormFile((root + "/" + std::to_string(i + 1) + ".png").c_str()));
    }
}
void SpriteAnimation::AddTexture(const char* path) {
    textures.push_back(ZERO_TEXTURE_MGR->LoadTextureFormFile(path));
    textureCount++;
}
void SpriteAnimation::ResetTexture() {
    textures.resize(0);
    textureCount = 0;
}
void SpriteAnimation::RestartAnimation() {
    currentFrame = 0.0f;
    isEnd = false;
    isLoopEnd = false;
}