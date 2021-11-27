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

class __attribute__ ((visibility ("default"))) ICollider : public Component {
public:
    ICollider();
    ~ICollider() override = default;
    ICollider (const ITab&);
    virtual IShape* GetShape() = 0;
    virtual int GetCollisionTag() const;
    virtual int GetCollisionFlag() const;
    virtual int GetCollisionMask() const;
    void setCollisionFlag(int);
    void setCollisionMask(int);
    void setCollisionTag(int);
    Bounds GetBounds() const;
    Bounds GetDynamicBounds () const;
    virtual Bounds getAttackBounds() const;
    Bounds getControllerBounds() const;
    void Start() override;
    void End() override;
    using ParentClass = ICollider;
    Event<ICollider*> onShapeChange;
    virtual float getAttackDistance() const = 0;
protected:
    void Move(Entity*);
    virtual Bounds GetStaticBoundsI () const = 0;
    virtual Bounds GetDynamicBoundsI () const = 0;
    ICollisionEngine* m_engine;
	Bounds m_controllerBounds;
	bool m_debug;
    int m_flag;
    int m_mask;
    int m_tag;
};


inline void ICollider::setCollisionFlag(int flag) {
    m_flag = flag;
}


inline void ICollider::setCollisionMask(int mask) {
    m_mask = mask;
}

inline void ICollider::setCollisionTag(int tag) {
    m_tag = tag;
}