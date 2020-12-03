#pragma once
#include "Component.h"
class RigidBody2D : public Component {
public:
    RigidBody2D() {};

    void LateUpdate() override;

    Vec2 GetVelocity() { return this->velocity; }
    double GetMass() { return this->mass; }
    double GetRestitution() { return this->restitution; }
    double GetGravity() { return this->gravity; }
    bool GetIsStrict() { return this->strict; }

    RigidBody2D* SetVelocity(Vec2 v) { 
        this->velocity = v;
        return this;
    }

    RigidBody2D* SetVelocity(double x, double y) {
        this->velocity = Vec2(x, y);
        return this;
    }

    RigidBody2D* AddVelocity(Vec2 v) { 
        this->velocity += v;
        return this;
    }

    RigidBody2D* SetMass(double m) {
        this->mass = m;
        return this;
    }

    RigidBody2D* SetRestitution(double r) { 
        this->restitution = r;
        return this;
    }

    RigidBody2D* SetGravity(double g) { 
        this->gravity = g;
        return this;
    }

    RigidBody2D* SetIsStrict(bool s) { 
        this->strict = s;
        return this;
    }

private:
    Vec2 velocity = Vec2(0.0, 0.0);
    double mass = 1.0;
    double inv_mass = 1.0;
    double restitution = 1.0;
    double gravity = 980.0;
    bool strict = false;
};

