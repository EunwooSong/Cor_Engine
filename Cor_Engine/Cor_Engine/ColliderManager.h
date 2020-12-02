#pragma once

#include <vector>
#include <unordered_set>

class BoxCollider;

class ColliderManager {
public:
    void MountCollider(BoxCollider* colA, BoxCollider* colB);

    std::vector<std::unordered_set<BoxCollider*>> GetColliderQueue();
    void Update();
    void LateUpdate();

private:
    std::vector<std::unordered_set<BoxCollider*>> colliderQueue{};
};

// isPreviousLoopCollisionResolved bool--