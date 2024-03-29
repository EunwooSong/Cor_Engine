#include "stdafx.h"
#include "ColliderManager.h"
#include "BoxCollider.h"
#include "GameObject.h"
#include "RigidBody2D.h"
#include "ZeroSystem.h"

void ColliderManager::MountCollider(BoxCollider* colA,
    BoxCollider* colB) {
    if (!colA || !colB) return;

    //CLogger::Info("MOUNT COLLIDER");
    std::unordered_set<BoxCollider*> colliderSet;
    colliderSet.insert(colA);
    colliderSet.insert(colB);
    for (auto iter : this->colliderQueue) {
        if (iter == colliderSet) {
            std::cout << "[ColliderManager] Collide case already exists!" << std::endl;
            return;
        }
    }
    this->colliderQueue.push_back(colliderSet);
}

std::vector<std::unordered_set<BoxCollider*>> ColliderManager::GetColliderQueue() {
    return this->colliderQueue;
}

namespace CalculateFunctions {
    Vec2 getHeightVector(BoxCollider* a) {
        Vec2 ret;
        ret.x = a->GetLeftTopPos().y * sinf(a->GetRotation()) / 2;
        ret.y = a->GetRightBottomPos().y * cosf(a->GetRotation()) / 2;
        return ret;
    }

    Vec2 getWidthVector(BoxCollider* a) {
        Vec2 ret;
        ret.x = a->GetRightBottomPos().x * cosf(a->GetRotation()) / 2;
        ret.y = a->GetLeftTopPos().x * sinf(a->GetRotation()) / 2;
        return ret;
    }

    Vec2 getUnitVector(Vec2 a) {
        Vec2 ret;
        float size;
        size = sqrt(pow(a.x, 2) + pow(a.y, 2));
        ret.x = a.x / size;
        ret.y = a.y / size;
        return ret;
    }

#define PI 3.14159265358979323846f

    float deg_to_rad(float deg) {
        return deg * PI / 180;
    }

    float rad_to_deg(float rad) {
        return rad * 180 / PI;
    }

    float dotProduct(Vec2& l, Vec2& r) {
        return l.x * r.x + l.y * r.y;
    }

    Vec2 crossProduct(Vec2 l, Vec2 r) {
        // TODO : TEST THIS
        Vec2 v;
        v.x = l.x * r.y;
        v.y = l.y * r.x;
        return v;
    }

    struct XYMinMax {
        struct xy {
            float x;
            float y;
        };
        xy min;
        xy max;
    };

    XYMinMax setMinMax(BoxCollider* collider) {
        XYMinMax xymm;

        xymm.min.x = collider->GetLeftTopPos().x;
        xymm.min.y = collider->GetLeftTopPos().y;
        xymm.max.x = collider->GetRightBottomPos().x;
        xymm.max.y = collider->GetRightBottomPos().y;

        std::cout << xymm.max.y << std::endl;

        return xymm;
    }
}

void evalCollision(BoxCollider* _A, BoxCollider* _B) {
    using namespace CalculateFunctions;

    auto A = _A->GetOwner()->GetComponent<RigidBody2D>();
    auto B = _B->GetOwner()->GetComponent<RigidBody2D>();

    Vec2 rv = B->GetVelocity() - A->GetVelocity();
    auto normal = crossProduct((_A->GetLeftTopPos() + _A->GetRightBottomPos()) / 2,
        (_A->GetLeftTopPos() + _A->GetRightBottomPos()) / 2);

    // Calculate relative velocity in terms of the normal direction
    float velAlongNormal = dotProduct(rv, normal);

    // Do not resolve if velocities are separating
    if (velAlongNormal > 0)
        return;

    // Calculate restitution
    float e = min(A->GetRestitution(), B->GetRestitution());

    // Calculate impulse scalar
    float j = -(1 + e) * velAlongNormal;
    j /= 1 / A->GetMass() + 1 / B->GetMass();

    // Apply impulse
    Vec2 impulse = j * normal;
    //        A->SetVelocity(- (1 / A->GetMass() * impulse));
    //        B->SetVelocity((1 / B->GetMass() * impulse));
    auto aVel = A->GetVelocity();
    auto bVel = B->GetVelocity();
    A->SetVelocity(Vec2(aVel.x, 0));
    B->SetVelocity(Vec2(bVel.x, 0));
}

bool EvalAABB(BoxCollider* A, BoxCollider* B) {
    using namespace CalculateFunctions;

    XYMinMax a{}, b{};

    a = setMinMax(A);
    b = setMinMax(B);

    std::cout << a.max.x << " " << a.min.x << std::endl;
    std::cout << a.max.y << " " << a.min.y << std::endl;
    std::cout << b.max.x << " " << b.min.x << std::endl;
    std::cout << b.max.y << " " << b.min.y << std::endl;

    if (a.max.x < b.min.x || a.min.x > b.max.x) return false;
    if (a.max.y < b.min.y || a.min.y > b.max.y) return false;

    return true;
}

bool EvalOBB(BoxCollider* A, BoxCollider* B) {
    using namespace CalculateFunctions;
    Vec2 dist = ((A->GetLeftTopPos() + A->GetRightBottomPos()) / 2) -
        ((B->GetLeftTopPos() + B->GetRightBottomPos()) / 2);
    Vec2 vec[4] = {
            getHeightVector(A),
            getHeightVector(B),
            getWidthVector(A),
            getWidthVector(B) };
    Vec2 unit;
    for (auto& i : vec) {
        double sum = 0;
        unit = getUnitVector(i);
        for (auto& j : vec) {
            sum += abs(j.x * unit.x + j.y * unit.y);
        }
        if (abs(dist.x * unit.x + dist.y * unit.y) > sum) {
            return false;
        }
    }
    return true;
}

void ColliderManager::LateUpdate() {
    for (auto iter : this->colliderQueue) {
        BoxCollider* valA = *iter.begin();
        BoxCollider* valB = *++iter.begin();

        if (valA == nullptr || valB == nullptr) {
            std::cout << "[ColliderMananger] Collider is NULL! - Skipping" << std::endl;
            continue;
        }

        bool isCollided;

        if (valA->GetRotation() == 0.0f && valB->GetRotation() == 0.0f) {
            isCollided = EvalAABB(valA, valB);
        }
        else {
            isCollided = EvalOBB(valA, valB);
        }

        if (isCollided) {
            if (!valA->GetIsTrigger() && !valB->GetIsTrigger()) {
                evalCollision(valA, valB);
                if (!valA->GetIsCollided()) {
                    valA->OnCollisionEnter(valB);
                }
                else {
                    valA->OnCollisionStay(valB);
                }

                if (!valB->GetIsCollided()) {
                    valB->OnCollisionEnter(valA);
                }
                else {
                    valB->OnCollisionStay(valA);

                }
            }
            else {
                if (!valA->GetIsCollided()) {
                    valA->OnTriggerEnter(valB);
                }
                else {
                    valA->OnTriggerStay(valB);
                }

                if (!valB->GetIsCollided()) {
                    valB->OnTriggerEnter(valA);
                }
                else {
                    valB->OnTriggerStay(valA);
                }
            }
            valA->SetIsCollided(true);
            valB->SetIsCollided(true);
        }
        else {
            if (!valA->GetIsTrigger() && !valB->GetIsTrigger()) {
                if (valA->GetIsCollided()) {
                    valA->OnCollisionExit(valB);
                }
                if (valB->GetIsCollided()) {
                    valB->OnCollisionExit(valA);
                }
            }
            else {
                if (valA->GetIsCollided()) {
                    valA->OnTriggerExit(valB);
                }

                if (valB->GetIsCollided()) {
                    valB->OnTriggerExit(valA);
                }
            }

            valA->SetIsCollided(false);
            valB->SetIsCollided(false);
        }
        //            CLogger::Debug("[ColliderManager] Collider started : status : %s",  );
        std::cout << (isCollided ? "true" : "false") << std::endl;

    }

}

void ColliderManager::Update() {
    auto colliderArray = ZERO_SCENE_MGR->GetCurrentScene()->GetComponentArray<BoxCollider>();
    if (colliderArray.size() == 0) {
        return;
    }

    this->colliderQueue.clear();
    this->colliderQueue.resize(0);

    for (auto iter : colliderArray) {
        for (auto _iter : colliderArray) {
            if (iter == _iter) {
                continue;
            }
            this->MountCollider(iter, _iter);
        }
    }
}