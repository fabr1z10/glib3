#pragma once

#include <gfx/components/ianimator.h>
#include <gfx/skeletalanimation.h>
#include <gfx/model/skeletalmodel.h>
class Renderer;

// a skeletal animator requires a skeletal model!
class SkeletalAnimator : public IAnimator {
public:
    // a sk anim requires a sk model, as a sprite anim requires a spirtemodel!
    SkeletalAnimator (std::shared_ptr<IModel> model);

    //SkeletalAnimator();
    SkeletalAnimator(const SkeletalAnimator&);
    virtual ~SkeletalAnimator() {}
    SkeletalModel* getModel() const;
    void AddBone (const std::string& id, Entity* bone, float length);
    void Start() override;
    void Update(double dt) override;
    void SetAnimation (const std::string& anim, bool forward = true) override;
    //std::string GetAnimation() const;
    std::shared_ptr<Component> clone() const override;
    bool IsComplete() const override;
    bool looped() const;
    std::type_index GetType() override;
    void setOffsetY (float, float);
    std::vector<float>& getAngles();
    using ParentClass = SkeletalAnimator;
protected:
    // the current animation
    //std::string m_animation;
    double m_time;
    int m_inc;
    bool m_forward;
    //std::string m_initAnim;
    SkeletalAnimation* m_currentAnim;
    std::unordered_map<std::string, Entity*> m_bones;
    std::unordered_map<std::string, float> m_bonesLength;
    // TODO move in a subclass
    Renderer* m_ls;
    Renderer* m_rs;
    float m_l_offset_y;
    float m_r_offset_y;
    std::shared_ptr<SkeletalModel> m_model;
    std::vector<float> m_angles;

    bool m_looped;
};


inline std::type_index SkeletalAnimator::GetType() {
    return std::type_index(typeid(IAnimator));
}

inline bool SkeletalAnimator::looped() const {
    return m_looped;
}

inline std::vector<float>& SkeletalAnimator::getAngles() {
    return m_angles;
}
