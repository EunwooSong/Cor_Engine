#pragma once
#include "Component.h"
#include "AnimationController.h"
#include "Enum.h"
#include "TeamManager.h"
#include "Transform.h"
#include "Sprite2DRenderer.h"
#include "RigidBody2D.h"

class UnitMovement :
    public Component
{
public:
    UnitMovement() : moveSpeed(300.0f), attackRange(200.0f), attackPower(10.0f),
        attackDelay(0.5f), stopRange(100.0f), hp(100.0f), attackTimer(0.0f),
        isHit(false), isMove(true), isAttack(false),
        _anim(nullptr), teamMgr(nullptr), tr(nullptr), renderer(nullptr),
        team(Team::NONE), type(UnitType::NONE)
    {};
    ~UnitMovement() {};

    void Start()  override;
    void Update() override;

    void Attack();
    void InitType(Team team, UnitType type);
    Team GetTeam() { return team; }
    UnitType GetType() { return type; }

    std::vector<GameObject*>::iterator myIter;

private:
    //Move
    float moveSpeed;
    float stopRange;

    //Attack
    float attackRange;
    float attackPower;
    float attackDelay;
    float attackTimer;

    //State
    float hp;
    bool isHit;
    bool isMove;
    bool isAttack;

    //Components
    AnimationController* _anim;
    TeamManager* teamMgr;
    Sprite2DRenderer* renderer;
    Transform* tr;
    RigidBody2D* rigid;

    Team team;
    UnitType type;
};