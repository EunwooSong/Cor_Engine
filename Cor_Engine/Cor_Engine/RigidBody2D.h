#pragma once
#include "Component.h"
class RigidBody2D : public Component {
public:
    RigidBody2D() = default;

    void LateUpdate() override;

    Vec2 GetVelocity() { return this->velocity; }
    float GetMass() { return this->mass; }
    float GetRestitution() { return this->restitution; }
    float GetGravity();

    void SetVelocity(Vec2 v) { this->velocity = v; }
    void AddVelocity(Vec2 v) { this->velocity += v; }

    void SetMass(float m) { this->mass = m; }
    void SetRestitution(float r) { this->restitution = r; }
    void SetGravity(float g) { this->gravity = g; }

private:
    Vec2 velocity;
    float mass;
    float restitution;
    float gravity = 980.0f;
};

