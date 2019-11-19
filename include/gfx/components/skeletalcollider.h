#pragma once

#include "gfx/components/icollider.h"
#include <gfx/components/skeletalanimator.h>
#include <gfx/model/skeletalmodel.h>

class IAnimator;
class Renderer;

/*
 * A skeletal collider needs to be used with a skeletalanimator.
 * it provides:
 *
 *  - one collision shape per animation
 *  - attack boxes. You can specify different boxes for (animation, time) pairs.
 *    when the animator passes the time, a box is casted and a collision test is performed
 *
 */

struct SkeletalAttackInfo {
    float time;
    std::shared_ptr<Shape> shape;
    int mask;
    int tag;
};

class SkeletalCollider : public ICollider {
public:
    SkeletalCollider(int flag, int mask, int tag) : ICollider(), m_flag(flag), m_mask(mask), m_tag(tag) {}
    SkeletalCollider(const SkeletalCollider&);
    std::shared_ptr<Component> clone() const override;
    void Start() override;
    void Update(double) override;
    std::type_index GetType() override;
    int GetCollisionTag() const;
    int GetCollisionFlag() const;
    int GetCollisionMask() const;
    Shape* GetShape() override;

private:
    Bounds GetStaticBoundsI() const override;
    Bounds GetDynamicBoundsI() const override;
    SkeletalAnimator* m_animator;
    SkeletalModel* m_model;
    int m_flag;
    int m_mask;
    int m_tag;
};


inline int SkeletalCollider::GetCollisionTag() const {
    return m_tag;
}

inline int SkeletalCollider::GetCollisionFlag() const {
    return m_flag;
}

inline int SkeletalCollider::GetCollisionMask() const {
    return m_mask;
}