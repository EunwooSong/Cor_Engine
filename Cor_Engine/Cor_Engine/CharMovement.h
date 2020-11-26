#pragma once
#include "Component.h"
class CharMovement :
    public Component
{
public:
    CharMovement() : time(0.0f) {};
    ~CharMovement() {};

    void Start() {};
    void Update();
    void Render() {};

    float time;
};

