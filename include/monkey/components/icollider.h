#pragma once

#include <monkey/component.h>
#include <monkey/math/shape.h>
#include <monkey/event.h>

class ICollisionEngine;

struct CollisionTriplet {
    int flag;
    int mask;
    int tag;
};

class ICollider : public Component {
public:
    ICollider();
    ~ICollider() override = default;
    virtual IShape* GetShape() = 0;
    virtual int GetCollisionTag() const = 0;
    virtual int GetCollisionFlag() const = 0;
    virtual int GetCollisionMask() const = 0;
    Bounds GetBounds() const;
    Bounds GetDynamicBounds () const;
    virtual Bounds getAttackBounds() const;
    Bounds getControllerBounds() const;
    void Start() override;
    void End() override;
    using ParentClass = ICollider;
    Event<ICollider*> onShapeChange;
protected:
    void Move(Entity*);
    virtual Bounds GetStaticBoundsI () const = 0;
    virtual Bounds GetDynamicBoundsI () const = 0;
    ICollisionEngine* m_engine;
	Bounds m_controllerBounds;
	bool m_debug;

};


