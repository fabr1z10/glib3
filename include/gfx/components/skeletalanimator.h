#pragma once

#include <gfx/component.h>
#include <gfx/skeletalanimation.h>

class SkeletalAnimator : public Component {
public:
    SkeletalAnimator();
    SkeletalAnimator(const SkeletalAnimator&);
    virtual ~SkeletalAnimator() {}
    void AddAnimation (std::shared_ptr<SkeletalAnimation> anim);
    void Start() override;
    void Update(double dt) override;
    void SetAnimation (const std::string& anim, bool forward = true);
    std::string GetAnimation() const;
    std::shared_ptr<Component> clone() const override;
    using ParentClass = SkeletalAnimator;
protected:
    std::unordered_map<std::string, std::shared_ptr<SkeletalAnimation>> m_animations;
    // the current animation
    std::string m_animation;
    double m_time;
    int m_inc;
    bool m_forward;
    std::string m_initAnim;
    SkeletalAnimation* m_currentAnim;
    std::unordered_map<std::string, Entity*> m_bones;
};


