#pragma once

#include <monkey/components/icollider.h>

class SkModel;
class SkAnimator;
class MultiRenderer;
/*
 * A smart collider needs to be used with a skeletal model.
 * You can associate a BOX to each animation, plus attack boxes
 * for (animation/interval) pairs
 *
 *
 */
class SkCollider : public ICollider {
public:
    // ctor and clone
    SkCollider(const SkCollider&);
    SkCollider (const ITable&);
    std::shared_ptr<Component> clone() const override;

    void Start() override;
    void Update(double) override;
    Shape* GetShape() override;

    int GetCollisionTag() const override;
    int GetCollisionFlag() const override;
    int GetCollisionMask() const override;
    int setCollisionMask(int);
    std::type_index GetType() override;
    Bounds getAttackBounds() const override;
private:
    SkAnimator* m_animator;
    Entity* m_shapeEntity;
    MultiRenderer* m_colliderRenderer;

    SkModel* m_model;
    Bounds GetStaticBoundsI() const override;
    Bounds GetDynamicBoundsI() const override;
    int m_flag;
    int m_mask;
    int m_tag;
    int m_castTag;
    int m_castMask;
};
