#pragma once
#include "stdafx.h"
#include "DirectXCore.h"
#include "WindowsApplication.h"
#include "SceneManager.h"

#define ZERO_ENGINE        SharkSystem::Instance()
#define ZERO_DIRECT3D      DIRECTX_CORE
#define ZERO_WINDOWS       WINDOWS_APPLICATION

#define ZERO_TIME_MGR      ZERO_ENGINE->SharkSystem::GetTimeManager()
#define ZERO_SCENE_MGR     ZERO_ENGINE->SharkSystem::GetSceneManager()
#define ZERO_INPUT_MGR     ZERO_ENGINE->SharkSystem::GetInputManager()
#define ZERO_TEXTURE_MGR   ZERO_ENGINE->SharkSystem::GetTextureManager()
#define ZERO_LINE_MGR      ZERO_ENGINE->SharkSystem::GetLineDebuggerManager()

class ZeroSystem {
public:
    static std::unique_ptr<ZeroSystem> instance;
    static std::once_flag onlyOnce;

    ZeroSystem() = default;

    ~ZeroSystem() = default;

    static ZeroSystem* Instance() {
        std::call_once(onlyOnce, []() { instance.reset(new ZeroSystem()); });

        return instance.get();
    };

    void InitializeEngine(std::string appName, int width, int height, bool isFullScreen) {
        ZERO_WINDOWS->RegisterInfo(appName, width, height, isFullScreen);
        ZERO_DIRECT3D->RegisterInfo(width, height, isFullScreen);


        ZERO_WINDOWS->Initialize();
        ZERO_DIRECT3D->Initialize(ZERO_WINDOWS->FloatWindow(10));

        sceneMgr = new SceneManager();
        timeMgr = new TimeManager();
        textureMgr = new DirectXTextureManger();
        inputMgr = new InputManager();
        lineMgr = new LineDebuggerManager();

        //Initialize Managers
        timeMgr->Init();
    };

    void Start() { sceneMgr->Start(); }
    bool Update() {
        if (ZERO_WINDOWS->CheckMessage().message == WM_QUIT)
            return false;

        timeMgr->Update();
        inputMgr->Update();
        sceneMgr->Update();

        return true;
    }
    void LateUpdate() { sceneMgr->LateUpdate(); }
    void Render() {
        ZERO_DIRECT3D->BeginRender();

        ZERO_DIRECT3D->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
        sceneMgr->Render();
        ZERO_DIRECT3D->GetSprite()->End();

        ZERO_DIRECT3D->GetLine()->Begin();
        lineMgr->Render();
        ZERO_DIRECT3D->GetLine()->End();

        ZERO_DIRECT3D->EndRender();
    }

    void EndScene() { sceneMgr->EndScene(); }

    void Release() {
        textureMgr->Release();

        SAFE_DELETE(sceneMgr);
        SAFE_DELETE(timeMgr);
        SAFE_DELETE(textureMgr);
        SAFE_DELETE(inputMgr);
        SAFE_DELETE(lineMgr);

        ZERO_DIRECT3D->Release();
    }

    bool IsClosed() const { return ZERO_WINDOWS->CheckMessage().message == WM_QUIT; }

    SceneManager* GetSceneManager() { return sceneMgr; };
    TimeManager* GetTimeManager() { return timeMgr; };
    InputManager* GetInputManager() { return inputMgr; };
    DirectXTextureManger* GetTextureManager() { return textureMgr; };
    LineDebuggerManager* GetLineDebuggerManager() { return lineMgr; }
public:
    SceneManager* sceneMgr;
    TimeManager* timeMgr;
    InputManager* inputMgr;
    DirectXTextureManger* textureMgr;
    LineDebuggerManager* lineMgr;

};