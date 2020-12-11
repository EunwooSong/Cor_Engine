#pragma once
#include "Component.h"
#include "Enum.h"

class PickSceneManager :
    public Component
{
public:
    void Start();
    void Update();

    void AddType(Team team, UnitType type);

    float timer = 0.0f;

    int index_1 = 0;
    int index_2 = 4;

    int count_1 = 0;
    int count_2 = 0;

    GameObject* pick_1_ui;
    GameObject* pick_2_ui;

    GameObject* btn_start;

    GameObject* typeList[5];

    UnitType typeList_1[3] = { UnitType::NONE, };
    UnitType typeList_2[3] = { UnitType::NONE, };
};