#pragma once

#include "gfx/components/icollider.h"

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
};

class SkeletalCollider : public ICollider {
public:
    SkeletalCollider(int flag, int mask, int tag) : ICollider(), m_flag(flag), m_mask(mask), m_tag(tag), m_currentAttackInfo(
            nullptr) {}
    SkeletalCollider(const SkeletalCollider&);
    void Start() override;
    void Update(double) override;
    Shape* GetShape() override;
    int GetCollisionTag() const override;
    int GetCollisionFlag() const override;
    int GetCollisionMask() const override;
    std::shared_ptr<Component> clone() const override;
    std::type_index GetType() override;
    void addBound (const std::string& animation, float x0, float y0, float w, float h, float scale);
    void addAttack (const std::string& animation, float t, float x0, float y0, float w, float h, int mask, float scale);
    void notifyAnimationChange (IAnimator*);
private:
    double m_time;
    IAnimator* m_animator;
    Bounds GetStaticBoundsI() const override;
    Bounds GetDynamicBoundsI() const override;
    Bounds m_maxBounds;
    Renderer* m_colliderRenderer;

    std::unordered_map<std::string, Bounds> m_animationBounds;
    std::unordered_map<std::string, glm::ivec2> m_animMeshInfo;
    int m_flag;
    int m_mask;
    int m_tag;
    std::unordered_map<std::string, SkeletalAttackInfo> m_attackInfos;
    SkeletalAttackInfo* m_currentAttackInfo;
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