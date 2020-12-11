#include "stdafx.h"
#include "ZeroSystem.h"
#include "GameScene.h"
#include "MainScene.h"
#include "RigidBodyTestScene.h"

#if defined(DEBUG) || defined(_DEBUG)
int main() {
#else
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT)
{
#endif

	bool isFullScreen = false;
	ZERO_ENGINE->RegisterEngine("ZeroEngine", 1280, 720, isFullScreen);

	ZERO_ENGINE->InitializeEngine();
	ZERO_SCENE_MGR->ChangeScene(new MainScene());
	ZERO_SOUND_MGR->LoadWaveFile("Resources/bgm_good.wav", "BGM");
	ZERO_SOUND_MGR->PlayWaveFile("BGM");
	
	return ZERO_ENGINE->MainLoop();
}