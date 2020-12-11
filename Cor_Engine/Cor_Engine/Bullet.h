#pragma once
#include "GameObject.h"
class Bullet :
    public GameObject
{
public:
    Bullet() : GameObject() { Init(); }
    ~Bullet() = default;

    void Init() override;
};

