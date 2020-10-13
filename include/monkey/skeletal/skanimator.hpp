#pragma once

#include <monkey/component.h>
#include <monkey/components/ianimator.h>
#include <monkey/skeletal/animation.hpp>
#include <monkey/skeletal/skmodel.hpp>
#include <monkey/components/renderer.h>

class SkAnimator : public IAnimator {
public:
    SkAnimator(std::shared_ptr<IModel>);
    SkAnimator(const SkAnimator&);
    std::shared_ptr<Component> clone() const override;

    virtual ~SkAnimator() {}
	void setSpeedUp(float);
    void setModel (std::shared_ptr<IModel> model) override;
    void Start() override;
    void Update(double dt) override;
    void SetAnimation (const std::string& anim, bool forward = true) override;
    bool IsComplete() const override;
    std::type_index GetType() override;
    IModel* getModel() const override;
    SkModel* getSkeletalModel() const;
    float getAnimationTime() const;
    using ParentClass = IAnimator;
protected:
    float m_animationTime;
    SkAnimation* m_currentAnimation;
    //std::string m_currentAnimId;
    std::shared_ptr<SkModel> m_model;
    Renderer* m_renderer;
private:
    std::unordered_map<std::string, glm::mat4> calculateCurrentAnimationPose();
    std::pair<SKeyFrame*, SKeyFrame*> getPreviousAndNextFrames();
    std::unordered_map<std::string, glm::mat4> interpolatePoses(SKeyFrame* previousFrame, SKeyFrame* nextFrame, float progression);
    void applyPoseToJoints(const std::unordered_map<std::string, glm::mat4>& currentPose, std::shared_ptr<Joint> joint, glm::mat4& parentTransform);

    std::vector<std::pair<std::string, glm::vec3>> m_offsetPoints;
    bool m_complete;
    float m_speedUp;
};


inline SkModel* SkAnimator::getSkeletalModel() const {
    return m_model.get();
}

inline float SkAnimator::getAnimationTime() const {
    return m_animationTime;

}