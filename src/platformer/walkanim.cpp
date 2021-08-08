#include "walkanim.h"

BasicWalkAnim::BasicWalkAnim(const std::string &idleAnim, const std::string &walkAnim) : m_idleAnim(idleAnim),
m_walkAnim(walkAnim) {}

BasicWalkAnim::BasicWalkAnim(const ITab & t) {
    m_idleAnim = t.get<std::string>("idle");
    m_walkAnim = t.get<std::string>("walk");
}
// works for both 2d and 3d
void BasicWalkAnim::animate(IAnimator * animator, const glm::vec3& velocity) {
    if (fabs(velocity.x) > 1.0f || fabs(velocity.z) > 1.0f) {
        animator->SetAnimation(m_walkAnim);
    } else {
        animator->SetAnimation(m_idleAnim);
    }
}

WalkYAnim::WalkYAnim(const std::string &idleAnimUp, const std::string &walkAnimUp, const std::string &idleAnimDown,
                     const std::string &walkAnimDown) : m_idleAnimUp(idleAnimUp), m_walkAnimUp(walkAnimUp),
                     m_idleAnimDown(idleAnimDown), m_walkAnimDown(walkAnimDown) {}

WalkYAnim::WalkYAnim(const ITab & t) {
    m_idleAnimUp = t.get<std::string>("idle_up");
    m_walkAnimUp = t.get<std::string>("walk_up");
    m_idleAnimDown = t.get<std::string>("idle_down");
    m_walkAnimDown = t.get<std::string>("walk_down");
}

void WalkYAnim::animate(IAnimator * animator, const glm::vec3& velocity) {
    if (velocity.z < -1.0f) {
        if (fabs(velocity.x) > 1.0f or fabs(velocity.z) > 1.0f) {
            animator->SetAnimation(m_walkAnimUp);
        } else {
            animator->SetAnimation(m_idleAnimUp);
        }
    } else {
        if (fabs(velocity.x) > 1.0f or fabs(velocity.z) > 1.0f) {
            animator->SetAnimation(m_walkAnimDown);
        } else {
            animator->SetAnimation(m_idleAnimDown);
        }
    }
}