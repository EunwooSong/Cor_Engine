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

    // ���� ���� üũ
    void CheckDeathUnit();

    // ���� ��ġ
    GameObject* teamBase1;
    GameObject* teamBase2;

    //���� Ž���� ����
    std::vector<GameObject*> team1_unit;
    std::vector<GameObject*> team2_unit;
};

