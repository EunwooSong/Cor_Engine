#pragma once
#include "ECS_Type.h"

class Collision;
class GameObject;
class Entity;

class Component {
public:
    Component() : isDestroy(false), isActive(true), isStarted(false), m_Owner(nullptr) {};
    virtual ~Component() {};
    virtual void Start() { isStarted = true; }
    virtual void Update() {}
    virtual void LateUpdate() {}
    virtual void Render() {}
    virtual void EndScene() {}

    void Destroy() { isDestroy = true; }
    static void Destroy(Component* compo) { compo->Destroy(); }
    bool GetIsDestroy() const { return isDestroy; }

    void SetActive(bool isActive) { this->isActive = isActive; }
    bool GetActive() const { return isActive; }

    GameObject* GetOwner();
    void SetOwner(Entity* owner) { m_Owner = owner; }

    bool GetIsStarted() { return isStarted; }

protected:
    Entity* m_Owner;
    bool isDestroy;
    bool isActive;
    bool isStarted;

    //Component Listeners
public:
    virtual void OnCollisionEnter(Collision* coll) {};
    virtual void OnCollisionStay(Collision* coll) {};
    virtual void OnCollisionExit(Collision* coll) {};
    virtual void OnTriggerEnter(Collision* coll) {};
    virtual void OnTriggerStay(Collision* coll) {};
    virtual void OnTriggerExit(Collision* coll) {};
};