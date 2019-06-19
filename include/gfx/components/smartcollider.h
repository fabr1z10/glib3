#pragma once

#include "gfx/components/icollider.h"

class Animator;
class BoxedModel;

/*
 * A smart collider needs to be used with a boxed model.
 * A boxed model is a model with collision boxes associated to each frame.
 *
 * When
 *
 */
class SmartCollider : public ICollider {
public:
    void Start() override;
    Shape* GetShape() override;
    int GetCollisionTag() const override;
    int GetCollisionFlag() const override;
    int GetCollisionMask() const override;
    Bounds GetBounds() const override;
private:
    Animator* m_animator;
    BoxedModel* m_model;
};
