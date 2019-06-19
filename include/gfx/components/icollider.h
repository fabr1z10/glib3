#pragma once

#include <gfx/component.h>
#include <gfx/math/shape.h>

class ICollider : public Component {
public:
    virtual Shape* GetShape() = 0;
    virtual int GetCollisionTag() const = 0;
    virtual int GetCollisionFlag() const = 0;
    virtual int GetCollisionMask() const = 0;
    virtual Bounds GetBounds() const = 0;
    using ParentClass = ICollider;

};


