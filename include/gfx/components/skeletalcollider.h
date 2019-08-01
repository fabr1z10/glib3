#pragma once

#include "gfx/components/icollider.h"

class SkeletalAnimator;

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


};

class SkeletalCollider : public ICollider {
public:
    SkeletalCollider(int flag, int mask, int tag) : ICollider(), m_flag(flag), m_mask(mask), m_tag(tag) {}
    SkeletalCollider(const SkeletalCollider&);
    void Start() override;
    void Update(double) override;
    Shape* GetShape() override;
    int GetCollisionTag() const override;
    int GetCollisionFlag() const override;
    int GetCollisionMask() const override;
    std::shared_ptr<Component> clone() const override;
    std::type_index GetType() override;
    void addBound (const std::string& animation, float x0, float y0, float w, float h);
private:
    SkeletalAnimator* m_animator;
    Bounds GetStaticBoundsI() const override;
    Bounds GetDynamicBoundsI() const override;
    Bounds m_maxBounds;
    std::unordered_map<std::string, Bounds> m_animationBounds;
    int m_flag;
    int m_mask;
    int m_tag;

};