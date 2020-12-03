#pragma once
#include "Enum.h"
#include "GameObject.h"
class UnitBaseObject :
    public GameObject
{
public:
    UnitBaseObject() : GameObject() { Init(); };
    ~UnitBaseObject() = default;

    void Init() override;
};

