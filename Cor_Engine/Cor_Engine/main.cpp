#include "stdafx.h"
#include "ZeroSystem.h"
#include "GameScene.h"

#if defined(DEBUG) || defined(_DEBUG)
int main() {
#else
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT)
{
#endif

	bool isFullScreen = true;
	ZERO_ENGINE->RegisterEngine("ZeroEngine", 1920, 1080, isFullScreen);

	ZERO_ENGINE->InitializeEngine();
	ZERO_SCENE_MGR->ChangeScene(new GameScene());
	
	return ZERO_ENGINE->MainLoop();
}