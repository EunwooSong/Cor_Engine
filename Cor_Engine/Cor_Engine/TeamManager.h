#pragma once
#include "Component.h"

class TeamManager :
    public Component
{
public:
    TeamManager();
    ~TeamManager();

    void Start() override;
    void Update() override;
    void LateUpdate() override;

    // 죽은 유닛 체크
    void CheckDeathUnit();

    // 생성 위치
    GameObject* teamBase1;
    GameObject* teamBase2;

    //빠른 탐색을 위함
    std::vector<GameObject*> team1_unit;
    std::vector<GameObject*> team2_unit;
};

