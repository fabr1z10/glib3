#include <monkey/skeletal/animation/skanimator2.hpp>

void SkAnimator2::Update(double dt) {

	if (m_currentAnimation == nullptr) {
		// set rest pose
		m_model->getRootJoint()->setRest();
		return;
	}

	// increase animation time
	m_animationTime += m_speedUp * dt;
	if (m_animationTime > m_currentAnimation->getLength()) {
		m_complete = true;
		m_animationTime = fmod(m_animationTime, m_currentAnimation->getLength());
	}
	auto currentPose = calculateCurrentAnimationPose();
	// pass the identity mat
	glm::mat4 I(1.0f);
	//applyPoseToJoints (currentPose, m_model->getRootJoint(), I);

	// apply offset
//	const auto& offsetPoints = m_model->getOffsetPoints();
//	if (!offsetPoints.empty()) {
//		glm::vec3 offset(0.0f);
//		//std::cout << "no of offset points: " << offsetPoints.size() << "\n";
//		for (const auto &a : offsetPoints) {
//
//			// find coordinates of offset pointg
//			glm::mat4 t = m_model->getJoint(a.first)->getAnimatedTransform();
//			glm::vec4 p = t * glm::vec4(a.second, 1.0f);
//			offset.y = std::max(-p.y, offset.y);
//		}
//		//std::cerr << offset.y << "\n";
//		m_renderer->SetTransform(glm::translate(offset));
//	}

}


std::unordered_map<std::string, glm::mat4> SkAnimator2::calculateCurrentAnimationPose() {
//	auto frames = getPreviousAndNextFrames();
//	float totalTime = frames.second->getTimeStamp() - frames.first->getTimeStamp();
//	float currentTime = m_animationTime - frames.first->getTimeStamp();
//	float progression = (totalTime == 0.0f) ? 0.0f : (currentTime / totalTime);
//	return interpolatePoses(frames.first, frames.second, progression);
}

std::pair<KeyFrame*, KeyFrame*> SkAnimator2::getPreviousAndNextFrames() {
//
//	const auto& allFrames = m_currentAnimation->getKeyFrames();
//	SKeyFrame* previousFrame = allFrames[0].get();
//	SKeyFrame* nextFrame = allFrames[0].get();
//	for (int i = 1; i < allFrames.size(); i++) {
//		nextFrame = allFrames[i].get();
//		if (nextFrame->getTimeStamp() > m_animationTime) {
//			break;
//		}
//		previousFrame = allFrames[i].get();
//	}
//	return std::make_pair(previousFrame, nextFrame);
}
