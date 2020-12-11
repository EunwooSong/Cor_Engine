#include "stdafx.h"
#include "ZeroSystem.h"

std::unique_ptr<ZeroSystem> ZeroSystem::instance;
std::once_flag ZeroSystem::onlyOnce;

ZeroSystem::ZeroSystem()
	: isDebug(false)
{
#if defined(DEBUG) | defined(_DEBUG)
	isDebug = true;
#endif
}

ZeroSystem::~ZeroSystem()
{
}

ZeroSystem* ZeroSystem::Instance()
{
	static ZeroSystem iter;
	return &iter;
}

void ZeroSystem::RegisterEngine(std::string appName, int width, int height, bool isFullScreen)
{
	ZERO_WINDOWS->RegisterInfo(appName, width, height, isFullScreen);
	ZERO_DIRECT3D->RegisterInfo(width, height, isFullScreen);
}

void ZeroSystem::InitializeEngine()
{
	ZERO_WINDOWS->Initialize();
	ZERO_DIRECT3D->Initialize(ZERO_WINDOWS->FloatWindow(10));//ZERO_WINDOWS->FloatWindow(10));

	sceneMgr = new SceneManager();
	timeMgr = new TimeManager();
	textureMgr = new DirectXTextureManager();
	inputMgr = new InputManager();
	soundMgr = new DirectXSoundManager();

	//Initialize Managers
	timeMgr->Init();
	soundMgr->Initialize(ZERO_WINDOWS->GetHWND());
}

void ZeroSystem::Start()
{
	timeMgr->Update();
	inputMgr->Update();

	sceneMgr->Start();
}

bool ZeroSystem::Update()
{
	sceneMgr->Update();
	return true;
}

void ZeroSystem::LateUpdate()
{
	sceneMgr->LateUpdate();
}

void ZeroSystem::Render()
{
	ZERO_DIRECT3D->BeginRender();

	ZERO_DIRECT3D->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	ZERO_DIRECT3D->GetDirect3DDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_NONE);
	ZERO_DIRECT3D->GetDirect3DDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_NONE);
	ZERO_DIRECT3D->GetDirect3DDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
	
	sceneMgr->Render();
	
	ZERO_DIRECT3D->GetSprite()->End();

	ZERO_DIRECT3D->EndRender();
}

void ZeroSystem::Release()
{
	textureMgr->Release();

	SAFE_DELETE(sceneMgr);
	SAFE_DELETE(timeMgr);
	SAFE_DELETE(textureMgr);
	SAFE_DELETE(inputMgr);
	SAFE_DELETE(soundMgr);
	
	ZERO_DIRECT3D->Release();
	instance.release();
}

bool ZeroSystem::IsClosed() const
{
	return ZERO_WINDOWS->CheckMessage().message == WM_QUIT;
}

int ZeroSystem::MainLoop()
{
	while (!IsClosed()) {
		Start();
		Update();
		LateUpdate();
		Render();
		EndScene();
	}

	Release();

#if defined(DEBUG) || defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif // defined(DEBUG)

	return 0;
}

bool ZeroSystem::GetIsDebug()
{
	return isDebug;
}
