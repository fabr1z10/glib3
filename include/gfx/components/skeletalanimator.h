#pragma once

#include <gfx/components/ianimator.h>
#include <gfx/skeletalanimation.h>

class SkeletalAnimator : public IAnimator {
public:
    SkeletalAnimator();
    SkeletalAnimator(const SkeletalAnimator&);
    virtual ~SkeletalAnimator() {}
    void AddAnimation (const std::string& id, std::shared_ptr<SkeletalAnimation> anim);
    void AddBone (const std::string& id, Entity* bone, float length);
    void Start() override;
    void Update(double dt) override;
    void SetAnimation (const std::string& anim, bool forward = true);
    std::string GetAnimation() const;
    std::shared_ptr<Component> clone() const override;
    bool IsComplete() const override;
    std::type_index GetType() override;

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
    std::unordered_map<std::string, float> m_bonesLength;
    // TODO move in a subclass
    float m_thighLength;
    float m_shinLength;
    std::unordered_map<std::string, float> m_angles;
};


inline std::type_index SkeletalAnimator::GetType() {
    return std::type_index(typeid(IAnimator));
}