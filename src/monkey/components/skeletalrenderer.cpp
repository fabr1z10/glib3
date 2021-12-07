#include <monkey/components/skeletalrenderer.h>


SkeletalRenderer::SkeletalRenderer(std::shared_ptr<Model> model) : AnimationRenderer(model)
{
	m_spriteModel = dynamic_cast<SkModel*>(model.get());
}

void SkeletalRenderer::Update(double) {
	auto pippo = m_spriteModel->calculateCurrentPose();
	std::cout << "ciao\n";
//	if (m_currentAnimation == nullptr) {
//		// set rest pose
//		m_model->getRootJoint()->setRest();
//		return;
//	}
//	// increase animation time
//	m_animationTime += m_speedUp * dt;
//	if (m_animationTime > m_currentAnimation->getLength()) {
//		m_complete = true;
//		if (m_currentAnimation->loop()) {
//			m_animationTime = fmod(m_animationTime, m_currentAnimation->getLength());
//		} else {
//			m_animationTime = m_currentAnimation->getLength() - 0.001f;
//		}
//	}
//	auto currentPose = calculateCurrentAnimationPose();
//	// pass the identity mat
//	glm::mat4 I(1.0f);
//	applyPoseToJoints (currentPose, m_model->getRootJoint(), I);
//
//	// apply offset
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

void SkeletalRenderer::Draw(Shader * s) {
	if (s->getShaderType() == ShaderType::SKELETAL_SHADER) {
		for (const auto& mesh : *m_model) {
			mesh->draw(s, 0, 0);
		}
	}

}

void SkeletalRenderer::setAnimation(const std::string &) {

}

std::type_index SkeletalRenderer::GetType() {
	return std::type_index(typeid(Renderer));
}