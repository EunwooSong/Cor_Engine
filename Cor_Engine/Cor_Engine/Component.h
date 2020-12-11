#pragma once
#include "ECS_Type.h"

class GameObject;
class Entity;
class BoxCollider;

class Component {
public:
    Component() : isDestroy(false), isActive(true), isStarted(false), m_Owner(nullptr) {};
    virtual ~Component() {};
    virtual void Start() { isStarted = true; }
    virtual void Update() {}
    virtual void LateUpdate() {}
    virtual void Render() {}
    virtual void EndScene() {}

    void Destroy()                          { isDestroy = true; }
    static void Destroy(Component* compo)   { compo->Destroy(); }
    bool GetIsDestroy() const               { return isDestroy; }

    void SetActive(bool isActive)           { this->isActive = isActive; }
    bool GetActive() const                  { return isActive; }

    GameObject* GetOwner();
    void SetOwner(Entity* owner)            { m_Owner = owner; }

    bool GetIsStarted()                     { return isStarted; }

protected:
    Entity* m_Owner;
    bool isDestroy;
    bool isActive;
    bool isStarted;

    //Component Listeners
public:
    virtual void OnCollisionEnter(BoxCollider* coll) {};
    virtual void OnCollisionStay(BoxCollider* coll) {};
    virtual void OnCollisionExit(BoxCollider* coll) {};
    virtual void OnTriggerEnter(BoxCollider* coll) {};
    virtual void OnTriggerStay(BoxCollider* coll) {};
    virtual void OnTriggerExit(BoxCollider* coll) {};
};