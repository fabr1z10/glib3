#pragma once

#include "gfx/components/icollider.h"

class Animator;
class BoxedModel;
class Renderer;

/*
 * A smart collider needs to be used with a boxed model.
 * A boxed model is a model with collision boxes associated to each frame.
 *
 * When
 *
 */
class SmartCollider : public ICollider {
public:
    SmartCollider() : ICollider() {}
    SmartCollider(const SmartCollider&);
    void Start() override;
    void Update(double) override {}
    Shape* GetShape() override;
    int GetCollisionTag() const override;
    int GetCollisionFlag() const override;
    int GetCollisionMask() const override;
    Bounds GetBounds() const override;
    std::shared_ptr<Component> clone() const override;
    std::type_index GetType() override;
    void ofu(Animator*a);
private:
    Animator* m_animator;
    BoxedModel* m_model;
    Renderer* m_colliderRenderer;
};
