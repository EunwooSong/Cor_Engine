#include "stdafx.h"
#include "SceneManager.h"

void SceneManager::Start() {
    if (currentScene) currentScene->Start();
}

void SceneManager::Update() {
    if (currentScene) currentScene->Update();
}

void SceneManager::LateUpdate() {
    if (currentScene) currentScene->LateUpdate();
}

void SceneManager::Render() {
    if (currentScene) currentScene->Render();
}

void SceneManager::EndScene() {
    if (currentScene) currentScene->EndScene();

    if (nextScene) {
        SAFE_DELETE(currentScene);
        currentScene = nextScene;
        nextScene = nullptr;

        currentScene->Init();
    }
}

void SceneManager::ChangeScene(Scene* scene)
{
    if (!scene) {
        throw std::runtime_error("This is not supported type(Scene Manager)");
    }

    if (currentScene) {
        nextScene = scene;
    }
    else {
        currentScene = scene;
        currentScene->Init();
    }
}

Scene* SceneManager::GetCurrentScene() {
    return currentScene;
}