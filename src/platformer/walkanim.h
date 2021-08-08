#pragma once

#include <monkey/components/ianimator.h>

class WalkAnim : public Ref {
public:
    virtual void animate(IAnimator*, const glm::vec3& velocity) = 0;
};

class BasicWalkAnim : public WalkAnim {
public:
    BasicWalkAnim(const ITab&);
    BasicWalkAnim(const std::string& idleAnim, const std::string& walkAnim);
    void animate(IAnimator*, const glm::vec3& velocity) override;
private:
    std::string m_idleAnim;
    std::string m_walkAnim;
};

// double dragon style. two different idle/walk sequences
// depending on whether you go up or down
class WalkYAnim : public WalkAnim {
public:
    WalkYAnim(const ITab&);
    WalkYAnim(const std::string& idleAnimUp, const std::string& walkAnimUp, const std::string& idleAnimDown, const std::string& walkAnimDown);
    void animate(IAnimator*, const glm::vec3& velocity) override;
private:
    std::string m_idleAnimUp;
    std::string m_walkAnimUp;
    std::string m_idleAnimDown;
    std::string m_walkAnimDown;
};


