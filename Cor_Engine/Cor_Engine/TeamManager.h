#pragma once
#include "Component.h"
#include "Enum.h"

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
    void CreateUnit(Team team);

    void SetUnitIndex(UnitType* arr1, UnitType* arr2);

    void CreateBullet(Team team, float damage, Vec2 pos);

    // 생성 위치
    GameObject* teamBase1;
    GameObject* teamBase2;
    GameObject* teamHp_1;
    GameObject* teamHp_2;

    // 생성 쿨타임

    //현재 인덱스
    int team1_currentIndex;
    bool createUnit_1;
    float createDelay_1;

    int team2_currentIndex;
    bool createUnit_2;
    float createDelay_2;

    //기지 상태, 체력, 돈, 레벨
    int defaultHp;

    int baseHp_1;
    int baseHp_2;

    float moneyTimer;
    float moneyDelay;
    int money_1;
    int money_2;

    int level_1;
    int level_2;


    //각자 고른 특별 유닛 정보
    UnitType indexArr1[6]{ UnitType::SWORD, UnitType::BOW, UnitType::SHIELD, UnitType::NONE, };
    UnitType indexArr2[6]{ UnitType::SWORD, UnitType::BOW, UnitType::SHIELD, UnitType::NONE, };

    //SWORD, BOW, SHIELD, SLAVE, MONKS, BUTCHERE, CLOWN, GISAENG
    int cost[8]{20, 25, 30, 50, 50, 50, 50, 50};


    //빠른 탐색을 위함
    std::vector<GameObject*> team1_unit;
    std::vector<GameObject*> team2_unit;
    std::vector<GameObject*> bullet_unit;
};