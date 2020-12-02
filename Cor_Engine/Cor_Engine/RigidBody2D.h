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

    void SetVelocity(Vec2 v) { this->velocity = v; }
    void SetVelocity(double x, double y) { this->velocity = Vec2(x, y); }
    void AddVelocity(Vec2 v) { this->velocity += v; }

    void SetMass(double m) { this->mass = m; }
    void SetRestitution(double r) { this->restitution = r; }
    void SetGravity(double g) { this->gravity = g; }
    void SetIsStrict(bool s) { this->strict = s; }

private:
    Vec2 velocity = Vec2(0.0, 0.0);
    double mass = 1.0;
    double inv_mass = 1.0;
    double restitution = 1.0;
    double gravity = 980.0;
    bool strict = false;
};

