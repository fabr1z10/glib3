#pragma once

#include <monkey/components/animrenderer.h>
#include <monkey/skeletal/skmodel.hpp>



class SkeletalRenderer : public AnimationRenderer {
public:
	SkeletalRenderer(std::shared_ptr<Model>);
	void Start() override;
	void Update(double) override;
	void Draw(Shader*) override;
	void setAnimation(const std::string&) override;
	float getAnimationTime() const;
	std::type_index GetType() override;
    SkModel* getModel();
	void setModel(std::shared_ptr<Model>) override;

private:
    std::unordered_map<int, JointTransform> interpolatePoses(
            SKeyFrame* previousFrame, SKeyFrame* nextFrame, float progression);


        //int m_frame;
	float m_animationTime;
	SkModel* m_spriteModel;
	SkAnimation* m_currentAnimation;
	std::string m_currentAnimationId;
    std::vector<glm::mat4> m_bones;
	//AnimationInfo* m_currentAnimInfo;
	//int m_frameCount;
	//double m_time;
};


inline SkModel * SkeletalRenderer::getModel() {
    return m_spriteModel;
}

inline float SkeletalRenderer::getAnimationTime() const {
	return m_animationTime;
}