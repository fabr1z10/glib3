#include <monkey/components/skeletalrenderer.h>


SkeletalRenderer::SkeletalRenderer(std::shared_ptr<Model> model) : AnimationRenderer(model)
{
	m_spriteModel = dynamic_cast<SkModel*>(model.get());
	m_currentAnimation = nullptr;
}

void SkeletalRenderer::Start() {
    AnimationRenderer::Start();
    setAnimation("walk");
}

std::unordered_map<int, JointTransform> SkeletalRenderer::interpolatePoses(
        SKeyFrame* previousFrame, SKeyFrame* nextFrame, float progression) {
    std::unordered_map<int, JointTransform> currentPose;
    const auto& nf = nextFrame->getJointKeyFrames();
    for (const auto& p : previousFrame->getJointKeyFrames()) {
        // the model might not have this joint ... in this case nothing to do
        int jointId = m_spriteModel->getJointId(p.first);
        if (jointId == -1) {
            continue;
        }

        // previousTransform is p.second
        JointTransform nextTransform = nf.at(p.first);
        //JointTransform currentTransform = m_model->getRestTransform(p.first);
        auto localTransform = JointTransform::interpolate(p.second, nextTransform, progression);
        //currentTransform += JointTransform::interpolate(p.second, nextTransform, progression);
        //currentTransform.z = 0;
        //std::cout << m_animationTime << " . " << currentTransform.alpha << "\n";
        currentPose.insert(std::make_pair(jointId, localTransform));
    }
    return currentPose;
}


void SkeletalRenderer::Update(double dt) {
    std::unordered_map<int, JointTransform> pose;
    if (m_currentAnimation != nullptr) {
        m_animationTime += static_cast<float>(dt);
        if (m_animationTime >= m_currentAnimation->getLength()) {
            m_complete = true;
            if (m_currentAnimation->loop()) {
                m_animationTime = fmod(m_animationTime, m_currentAnimation->getLength());
            }  else {
    			m_animationTime = m_currentAnimation->getLength() - 0.001f;
            }
        }
        // compute current pose
        auto frames = m_currentAnimation->getPreviousAndNextKeyFrames(m_animationTime);
        pose = interpolatePoses(std::get<0>(frames), std::get<1>(frames), std::get<2>(frames));
    }

	m_bones = m_spriteModel->calculateCurrentPose(pose);

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

        auto boneLoc = glGetUniformLocation(s->getProgId(), "Bone");
        auto l2m = glGetUniformLocation(s->getProgId(), "local_to_model");
        auto weightIndex = glGetUniformLocation(s->getProgId(), "weightIndex");
	    glUniformMatrix4fv(boneLoc, m_bones.size(), false, &m_bones[0][0][0]);
		int n = 0;
	    for (const auto& mesh : *m_model) {
		    // set local to model
		    auto restTransform = m_spriteModel->getRestTransform(n);
		    auto weightIndices = m_spriteModel->getWeightIndex(n++);
		    glUniformMatrix4fv(l2m, 1, false, &restTransform[0][0]);
		    glUniform3iv(weightIndex, 1, &weightIndices[0]);
			mesh->draw(s, 0, 0);
		}
	}

}

void SkeletalRenderer::setAnimation(const std::string & id) {
    if (id == m_currentAnimationId) {
        return;
    }

    m_complete = false;
    m_currentAnimation = m_spriteModel->getAnimation(id);
    m_animationTime = 0.0f;
}

std::type_index SkeletalRenderer::GetType() {
	return std::type_index(typeid(Renderer));
}