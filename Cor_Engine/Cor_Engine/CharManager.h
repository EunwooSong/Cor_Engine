#pragma once
#include "Component.h"
class CharManager :
    public Component
{
public:
    CharManager() {};
    ~CharManager() {};

    void Update() override;
};

