#pragma once
#include "Scene.h"
class Scene;

class SceneManager {
public:
    SceneManager() : currentScene(nullptr), nextScene(nullptr) {};
    ~SceneManager();

    Scene* GetCurrentScene();

    void Start();
    void Update();
    void LateUpdate();
    void Render();
    void EndScene();

    void ChangeScene(Scene* scene);

private:
    Scene* currentScene;
    Scene* nextScene;
};