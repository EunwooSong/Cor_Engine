#pragma once
#include "Scene.h"
#include "Enum.h"

class ResultScene :
    public Scene
{
public:
    void Init() override;

public:
    Team winTeam;
};

