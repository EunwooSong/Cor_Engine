#include "stdafx.h"
#include "ColliderManager.h"
#include "BoxCollider.h"
#include "GameObject.h"
#include "RigidBody2D.h"
#include "ZeroSystem.h"
#include <cstdlib>

void ColliderManager::MountCollider(BoxCollider* colA,
    BoxCollider* colB) {
    if (!colA || !colB) return;

    //CLogger::Info("MOUNT COLLIDER");
    std::unordered_set<BoxCollider*> colliderSet;
    colliderSet.insert(colA);
    colliderSet.insert(colB);
    for (auto iter : this->colliderQueue) {
        if (iter == colliderSet) {
            CLogger::Debug("[ColliderManager] Collide case already exists!");
            return;
        }
    }
    this->colliderQueue.push_back(colliderSet);
}

std::vector<std::unordered_set<BoxCollider*>> ColliderManager::GetColliderQueue() {
    return this->colliderQueue;
}

namespace CalculateFunctions {

    constexpr double PI = 3.14159265358979;

    enum class AABBDirection {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };

    double deg_to_rad(double deg) {
        return deg / 180 * PI;
    }

    double rad_to_deg(double rad) {
        return rad * 180 / PI;
    }

    double getLength(Vec2 a) {
        return (double)sqrt(pow(a.x, 2) + pow(a.y, 2));
    }
   
    Vec2 normalizeVector(Vec2 a) {
        auto len = getLength(a);
        Vec2 ret(a.x / len, a.y / len);
        return ret;
    }
         
    Vec2 getHeightVector(BoxCollider* a) {
        Vec2 ret;
        ret.x = (double)a->GetScaleValue().y * 2 * cos(deg_to_rad(a->GetRotation() - 90)) / 2;
        ret.x = (double)a->GetScaleValue().y * 2 * sin(deg_to_rad(a->GetRotation() - 90)) / 2;
        return ret;
    }

    Vec2 getWidthVector(BoxCollider* a) {
        Vec2 ret;
        ret.x = (double)a->GetScaleValue().x * 2 * cos(deg_to_rad(a->GetRotation())) / 2;
        ret.y = (double)a->GetScaleValue().x * 2 * sin(deg_to_rad(a->GetRotation())) / 2;
        return ret;
    }

    Vec2 getUnitVector(Vec2 a) {
        Vec2 ret;
        double size;
        size = sqrt(pow(a.x, 2) + pow(a.y, 2));
        ret.x = a.x / size;
        ret.y = a.y / size;
        return ret;
    }

    Vec2 getDistanceVector(BoxCollider* a, BoxCollider* b) {
        return a->GetCenterPos() - b->GetCenterPos();
    }

    double dotProduct(Vec2& l, Vec2& r) {
        return (double)l.x * r.x + (double)l.y * r.y;
    }

    Vec2 addVector(Vec2 a, Vec2 b) {
        Vec2 ret;
        ret.x = a.x + b.x;
        ret.y = a.y + b.y;
        return ret;
    }

    double absDotVector(Vec2 a, Vec2 b) {
        return abs(a.x * b.x + a.y * b.y);
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

    AABBDirection getInverseVectorDirection(AABBDirection d) {
        switch (d) {
        case AABBDirection::UP:
            return AABBDirection::DOWN;
        case AABBDirection::DOWN:
            return AABBDirection::UP;
        case AABBDirection::LEFT:
            return AABBDirection::RIGHT;
        case AABBDirection::RIGHT:
            return AABBDirection::LEFT;
        }
    }

    struct AABBCollision {
        BoxCollider *collider;
        AABBDirection direction;
        AABBCollision(BoxCollider* c, AABBDirection d) {
            this->collider = c;
            this->direction = d;
        }
    };

    Vec2 getIntersectionDepth(BoxCollider* a, BoxCollider* b) {
        struct Vec2_D {
            double x;
            double y;
        };

        Vec2_D Distance;
        Distance.x = (double)a->GetCenterPos().x - b->GetCenterPos().x;
        Distance.y = (double)a->GetCenterPos().y - b->GetCenterPos().y;

        Vec2_D MinDistance;
        MinDistance.x = (double)a->GetScaleValue().x + b->GetScaleValue().x;
        MinDistance.y = (double)a->GetScaleValue().y + b->GetScaleValue().y;

        if (abs(Distance.x) >= MinDistance.x || abs(Distance.y) >= MinDistance.y) {
            return Vec2(0, 0);
        }

        Vec2_D Depth;
        Depth.x = Distance.x > 0 ? MinDistance.x - Distance.x : -MinDistance.x - Distance.x;
        Depth.y = Distance.y > 0 ? MinDistance.y - Distance.y : -MinDistance.y - Distance.y;

        return Vec2(Depth.x, Depth.y);
    }
}

void evalCollision(BoxCollider* _A, BoxCollider* _B) {
    system("pause");

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
    //A->AddVelocity(-1 * (1 / A->GetMass() * impulse));
    //B->AddVelocity(1 / B->GetMass() * impulse);
    //auto aVel = A->GetVelocity();
    //auto bVel = B->GetVelocity();
    //A->SetVelocity(Vec2(aVel.x, 0));
    //B->SetVelocity(Vec2(bVel.x, 0));
}

void ResolveAABB(CalculateFunctions::AABBCollision* A, CalculateFunctions::AABBCollision* B) {
    using namespace CalculateFunctions;

    if (A->collider->GetIsPreviousLoopCollisionResolved() || B->collider->GetIsPreviousLoopCollisionResolved()) {
        A->collider->SetIsPreviousLoopCollisionResolved(false);
        B->collider->SetIsPreviousLoopCollisionResolved(false);

        CLogger::Debug("Previous collision resolved");

        return;
    }
    else {
        A->collider->SetIsPreviousLoopCollisionResolved(true);
        B->collider->SetIsPreviousLoopCollisionResolved(true);
    }

    RigidBody2D* Arg = A->collider->GetOwner()->GetComponent<RigidBody2D>();
    RigidBody2D* Brg = B->collider->GetOwner()->GetComponent<RigidBody2D>();


    switch (A->direction) {
    case AABBDirection::UP:
    case AABBDirection::DOWN:
    {
        if (Arg->GetIsStrict() && Brg->GetIsStrict()) {
            return;
        }
        else if (Arg->GetIsStrict()) {
            double newBVelocity = Brg->GetVelocity().y * -1.0 * Brg->GetMass() * Arg->GetRestitution();
            Brg->SetVelocity(Vec2(Brg->GetVelocity().x, newBVelocity));

            return;
        }
        else if (Brg->GetIsStrict()) {
            double newAVelocity = Arg->GetVelocity().y * -1.0 * Arg->GetMass() * Brg->GetRestitution();
            Arg->SetVelocity(Vec2(Arg->GetVelocity().x, newAVelocity));

            return;
        }

        double newAVelocity = Brg->GetVelocity().y * Brg->GetMass() * Arg->GetRestitution();
        double newBVelocity = Arg->GetVelocity().y * Arg->GetMass() * Brg->GetRestitution();

        CLogger::Debug("AVel : %f BVel : %f", newAVelocity, newBVelocity);
        CLogger::Debug("AMass : %f, BMass : %f, ALegVel : %f, BLegVel : %f, Ares : %f, Bres : %f",
            Arg->GetMass(), Brg->GetMass(), Arg->GetVelocity().y, Brg->GetVelocity().y,
            Arg->GetRestitution(), Brg->GetRestitution());

        //system("pause");

        Arg->SetVelocity(Vec2(Arg->GetVelocity().x, newAVelocity));
        Brg->SetVelocity(Vec2(Brg->GetVelocity().x, newBVelocity));

        return;
    }
    case AABBDirection::LEFT:
    case AABBDirection::RIGHT:
    {
        if (Arg->GetIsStrict() && Brg->GetIsStrict()) {
            return;
        }
        else if (Arg->GetIsStrict()) {
            double newBVelocity = Brg->GetVelocity().x * -1.0 * Brg->GetMass() * Arg->GetRestitution();
            Brg->SetVelocity(Vec2(newBVelocity, Brg->GetVelocity().y));

            return;
        }
        else if (Brg->GetIsStrict()) {
            double newAVelocity = Arg->GetVelocity().x * -1.0 * Arg->GetMass() * Brg->GetRestitution();
            Arg->SetVelocity(Vec2(newAVelocity, Arg->GetVelocity().y));

            return;
        }

        double newAVelocity = Brg->GetVelocity().x * Brg->GetMass() * Arg->GetRestitution();
        double newBVelocity = Arg->GetVelocity().x * Arg->GetMass() * Brg->GetRestitution();

        Arg->SetVelocity(Vec2(newAVelocity, Arg->GetVelocity().y));
        Brg->SetVelocity(Vec2(newBVelocity, Brg->GetVelocity().y));

        return;
    }
    }
}

void ResolveAABB(BoxCollider* A, BoxCollider* B) {
    using namespace CalculateFunctions;
    auto intersection = getIntersectionDepth(A, B);
    
    if (intersection.x == 0 || intersection.y == 0) {
        return;
    }

    AABBDirection dirA;


    if ( abs(intersection.x) < abs(intersection.y) ) {
        // Collision on X asis
        if (sin(intersection.x) < 0) {
            // Collision on right
            dirA = AABBDirection::RIGHT;
        }
        else {
            // Collision on left
            dirA = AABBDirection::LEFT;
        }
    }
    else if ( abs(intersection.x) > abs(intersection.y) ) {
        // Collision on Y axis
        if (sin(intersection.y) < 0) {
            //Collision on bottom
            dirA = AABBDirection::DOWN;
        }
        else {
            //Collision on top
            dirA = AABBDirection::UP;
        }
    }

    AABBCollision ACol(A, dirA), BCol(B, getInverseVectorDirection(dirA));

    ResolveAABB(&ACol, &BCol);
}

bool EvalAABB(BoxCollider* A, BoxCollider* B) {
    using namespace CalculateFunctions;

    XYMinMax a{}, b{};

    a = setMinMax(A);
    b = setMinMax(B);

    CLogger::Debug("AABB COLLISION");
    CLogger::Debug("%f %f\n%f %f\n%f %f\n%f %f", a.max.x, a.min.x, a.max.y, a.min.y, b.max.x, b.min.x, b.max.y, b.min.y);

    if (a.max.x < b.min.x || a.min.x > b.max.x) return false;
    if (a.max.y < b.min.y || a.min.y > b.max.y) return false;

    return true;
}

bool EvalOBB(BoxCollider* A, BoxCollider* B) {
    CLogger::Debug("OBB COLLISION");

    using namespace CalculateFunctions;
    Vec2 dist = getDistanceVector(A, B);
    Vec2 vec[4] = {
            getHeightVector(A),
            getHeightVector(B),
            getWidthVector(A),
            getWidthVector(B) };
    Vec2 unit;
    for (int i = 0; i < 4; i++) {
        double sum = 0;
        unit = getUnitVector(vec[i]);
        for (int j = 0; j < 4; j++) {
            sum += absDotVector(vec[j], unit);
        }
        if (absDotVector(dist, unit) > sum) {
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
            CLogger::Info("[ColliderMananger] Collider is NULL! - Skipping");
            continue;
        }

        bool isCollided;

        if (valA->GetRotation() == 0.0f && valB->GetRotation() == 0.0f) {
            isCollided = EvalAABB(valA, valB);
        }
        else {
            isCollided = EvalOBB(valA, valB);
        }

        CLogger::Debug("[ColliderManager] Collider started : status : %s", isCollided ? "true" : "false");

        if (isCollided) {
            if (!valA->GetIsTrigger() && !valB->GetIsTrigger()) {
                //evalCollision(valA, valB)

                if (!valA->GetIsCollided()) {
                    using namespace CalculateFunctions;

                    /*auto direction = getVectorDirection(valA->GetCenterPos() - valB->GetCenterPos());
                    AABBCollision aC(valA, direction);
                    AABBCollision bC(valB, getInverseVectorDirection(direction));*/

                    //ResolveAABB(&aC, &bC);

                    ResolveAABB(valA, valB);


                    valA->OnCollisionEnter(valB);
                }
                else {

                    valA->OnCollisionStay(valB);
                }

                if (!valB->GetIsCollided()) {
                    valB->OnCollisionEnter(valA);
                }
                else {
                    valA->OnCollisionStay(valB);
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