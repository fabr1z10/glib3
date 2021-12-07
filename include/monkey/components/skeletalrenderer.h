#pragma once

#include <monkey/components/animrenderer.h>
#include <monkey/skeletal/skmodel.hpp>



class SkeletalRenderer : public AnimationRenderer {
public:
	SkeletalRenderer(std::shared_ptr<Model>);
	void Update(double) override;
	void Draw(Shader*) override;
	void setAnimation(const std::string&) override;
	float getAnimationTime() const;
	std::type_index GetType() override;

private:
	//int m_frame;
	float m_animationTime;
	SkModel* m_spriteModel;
	SkAnimation* m_currentAnimation;

	//AnimationInfo* m_currentAnimInfo;
	//int m_frameCount;
	//double m_time;
};

inline float SkeletalRenderer::getAnimationTime() const {
	return m_animationTime;
}