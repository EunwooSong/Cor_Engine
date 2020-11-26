#pragma once
#include "stdafx.h"
#include "DirectXCore.h"
#include "WindowsApplication.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "DirectXTextureManager.h"


#define ZERO_ENGINE        ZeroSystem::Instance()
#define ZERO_DIRECT3D      DIRECTX_CORE
#define ZERO_WINDOWS       WINDOWS_APPLICATION

#define ZERO_TIME_MGR      ZERO_ENGINE->GetTimeManager()
#define ZERO_SCENE_MGR     ZERO_ENGINE->GetSceneManager()
#define ZERO_INPUT_MGR     ZERO_ENGINE->GetInputManager()
#define ZERO_TEXTURE_MGR   ZERO_ENGINE->GetTextureManager()

class ZeroSystem {
public:
    static std::unique_ptr<ZeroSystem> instance;
    static std::once_flag onlyOnce;

    ZeroSystem() = default;
    ~ZeroSystem();

    static ZeroSystem* Instance();

    void RegisterEngine(std::string appName, int width, int height, bool isFullScreen);

    void InitializeEngine();

    void Start();
    bool Update();
    void LateUpdate();
    void Render();

    void EndScene() { sceneMgr->EndScene(); }

    void Release();

    bool IsClosed() const;
    int MainLoop();
    
    SceneManager* GetSceneManager()                 { return sceneMgr; }
    TimeManager* GetTimeManager()                   { return timeMgr; }
    InputManager* GetInputManager()                 { return inputMgr; }
    DirectXTextureManager* GetTextureManager()       { return textureMgr; }
public:
    SceneManager* sceneMgr;
    TimeManager* timeMgr;
    InputManager* inputMgr;
    DirectXTextureManager* textureMgr;
};