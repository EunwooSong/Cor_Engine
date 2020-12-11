#pragma once
#include "Component.h"
#include "Enum.h"
#include "Transform.h"

class BulletMovement :
    public Component
{
public:
    BulletMovement();
    ~BulletMovement();

    void Start() override;
    void Update() override;

    void InitBullet(Team team, BulletType type, float damage);

public:
    BulletType type;
    Team team;
    float damage;
    float moveSpeed;
    Transform* tr;
    float timer;
};

