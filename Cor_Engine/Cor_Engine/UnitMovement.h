#pragma once
#include "Component.h"
#include "AnimationController.h"
#include "Enum.h"
#include "TeamManager.h"
#include "Transform.h"
#include "Sprite2DRenderer.h"
#include "RectCollider.h"
#include "UIHp.h"

class UnitMovement :
    public Component
{
public:
    UnitMovement() : moveSpeed(75.0f), attackRange(100.0f), attackPower(10.0f),
        attackDelay(0.5f), stopRange(50.0f), hp(100.0f), attackTimer(0.0f), attackCurrentDelay(0.0f),
        isHit(false), isMove(true), isAttack(false),
        _anim(nullptr), teamMgr(nullptr), tr(nullptr), renderer(nullptr), rectColl(nullptr),
        attackTarget(nullptr),
        team(Team::NONE), type(UnitType::NONE)
    {};
    ~UnitMovement() {};

    void Start()  override;
    void Update() override;
    void LateUpdate() override;

    void Attack();
    void InitType(Team team, UnitType type);
    void GetDamage(float damage);
    Team GetTeam() { return team; }
    UnitType GetType() { return type; }

    float GetHp() { return hp; }
    float GetMaxHp() { return maxHp; }

    std::vector<GameObject*>::iterator myIter;

public:
    //Move
    float moveSpeed;
    float stopRange;

    //Attack
    float attackRange;
    float attackPower;
    float attackCurrentDelay;
    float attackDelay;
    float attackTimer;

    //State
    float hp;
    float maxHp;
    bool isHit;
    bool isMove;
    bool isAttack;

    //Components
    AnimationController* _anim;
    TeamManager* teamMgr;
    Sprite2DRenderer* renderer;
    Transform* tr;
    RectCollider* rectColl;

    //Attack Target
    UnitMovement* attackTarget;

    //UI HP bar
    UIHp* bar;

    Team team;
    UnitType type;
};