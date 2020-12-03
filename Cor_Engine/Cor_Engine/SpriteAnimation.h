#pragma once

class SpriteAnimation {
public:
    SpriteAnimation() : fps(0.0f),
        textureCount(0),
        isLoop(true),
        isLoopEnd(true),
        isEnd(true),
        currentFrame(0),
        timeCheck(0)
    {};
    ~SpriteAnimation() {};

    void Update();

    void AddTextures(std::string root, int textureCount);
    void AddTexture(const char* path);

    void ResetTexture();
    void RestartAnimation();

    float GetFps() { return fps; }
    int GetTextureCount() { return textureCount; }
    bool GetIsAnimationLoop() { return isLoop; }
    bool GetIsAnimationEnd() { return isLoopEnd || isEnd; }
    float GetCurrentFrame() { return currentFrame; }
    LPDIRECT3DTEXTURE9* GetCurrentFrameTexture() { return textures[(int)currentFrame]; }

    void SetFps(float fps) { this->fps = fps; }
    void SetIsLoop(bool isLoop) { this->isLoop = isLoop; }

private:
    std::vector<LPDIRECT3DTEXTURE9*> textures;
    float fps;
    int textureCount;
    bool isLoop;
    bool isLoopEnd;
    bool isEnd;
    float currentFrame;
    float timeCheck;
};