#pragma once
#include "Enum.h"
#include "Scene.h"
class GameScene :
    public Scene
{
public:
    GameScene();
    ~GameScene();

    void Init() override;

    UnitType arr[2][3];
};

