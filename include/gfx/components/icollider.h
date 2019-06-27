#pragma once

#include <gfx/component.h>
#include <gfx/math/shape.h>

class CollisionEngine;

class ICollider : public Component {
public:
    ICollider();
    virtual Shape* GetShape() = 0;
    virtual int GetCollisionTag() const = 0;
    virtual int GetCollisionFlag() const = 0;
    virtual int GetCollisionMask() const = 0;
    Bounds GetBounds() const;
    Bounds GetDynamicBounds () const;
    void Start() override;
    void End() override;
    using ParentClass = ICollider;
protected:
    void Move(Entity*);
    virtual Bounds GetStaticBoundsI () const = 0;
    virtual Bounds GetDynamicBoundsI () const = 0;
    CollisionEngine* m_engine;

};


