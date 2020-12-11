#pragma once
#include "Component.h"
#include "GameObject.h"
#include "TeamManager.h"
#include "UIText.h"
#include "Enum.h"

class UserPickUIManager :
    public Component
{
public:
    UserPickUIManager();
    ~UserPickUIManager();

    void Start();
    void Update();

    void Init(UnitType* arr1, UnitType* arr2);


public:
    int team1_pick;
    int team2_pick;

    float timer;

    GameObject* pick_ui_1;
    GameObject* pick_ui_2;

    UIText* money_text_1;
    UIText* money_text_2;

    GameObject* team1_ui[6];
    GameObject* team2_ui[6];

    TeamManager* teamMGR;
};