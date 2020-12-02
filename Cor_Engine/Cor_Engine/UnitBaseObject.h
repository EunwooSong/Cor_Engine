#pragma once
#include "Enum.h"
#include "GameObject.h"
class UnitBaseObject :
    public GameObject
{
public:
    UnitBaseObject() = default;
    ~UnitBaseObject() = default;

    void Init() override;
};

