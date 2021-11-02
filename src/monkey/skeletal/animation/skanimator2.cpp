//#include <monkey/skeletal/animation/skanimator2.hpp>
//
//SkAnimator2::SkAnimator2(std::shared_ptr<IModel> model) : IAnimator(),
//	m_currentAnimation(nullptr), m_complete(false), m_speedUp(1.0f)
//{
//	m_model = std::dynamic_pointer_cast<SkModel>(model);
//	m_initAnim = m_model->getDefaultAnimation();
//}
//
//void SkAnimator2::setSpeedUp(float value) {
//	m_speedUp = value;
//}
//
//
//void SkAnimator2::Update(double dt) {
//
//	if (m_currentAnimation == nullptr) {
//		// set rest pose
//		m_model->getRootJoint()->setRest();
//		return;
//	}
//
//	// increase animation time
//	m_animationTime += m_speedUp * dt;
//	if (m_animationTime > m_currentAnimation->getLength()) {
//		m_complete = true;
//		m_animationTime = fmod(m_animationTime, m_currentAnimation->getLength());
//	}
//	auto currentPose = calculateCurrentAnimationPose();
//	// pass the identity mat
//	glm::mat4 I(1.0f);
//	applyPoseToJoints (currentPose, m_model->getRootJoint(), I);
//
//	// apply offset ... 4 later
////	const auto& offsetPoints = m_model->getOffsetPoints();
////	if (!offsetPoints.empty()) {
////		glm::vec3 offset(0.0f);
////		//std::cout << "no of offset points: " << offsetPoints.size() << "\n";
////		for (const auto &a : offsetPoints) {
////
////			// find coordinates of offset pointg
////			glm::mat4 t = m_model->getJoint(a.first)->getAnimatedTransform();
////			glm::vec4 p = t * glm::vec4(a.second, 1.0f);
////			offset.y = std::max(-p.y, offset.y);
////		}
////		//std::cerr << offset.y << "\n";
////		m_renderer->SetTransform(glm::translate(offset));
////	}
//
//}
//
//void SkAnimator2::Start() {
//	m_animationTime = 0.0f;
//	if (!m_initAnim.empty()) {
//		SetAnimation(m_initAnim);
//	}
//	//m_renderer = m_entity->GetComponent<Renderer>();
//}
//
//
//std::unordered_map<std::string, glm::mat4> SkAnimator2::calculateCurrentAnimationPose() {
//	auto frames = m_currentAnimation->getPreviousAndNextKeyFrames(m_animationTime);
////	auto frames = getPreviousAndNextFrames();
////	float totalTime = frames.second->getTimeStamp() - frames.first->getTimeStamp();
////	float currentTime = m_animationTime - frames.first->getTimeStamp();
////	float progression = (totalTime == 0.0f) ? 0.0f : (currentTime / totalTime);
//	return interpolatePoses(std::get<0>(frames), std::get<1>(frames), std::get<2>(frames));
//}
//
//std::unordered_map<std::string, glm::mat4> SkAnimator2::interpolatePoses(KeyFrameSkeletal* previousFrame,
//	KeyFrameSkeletal* nextFrame, float progression) {
//
//	std::unordered_map<std::string, glm::mat4> currentPose;
//	const auto& nf = nextFrame->getJointKeyFrames();
//	for (const auto& p : previousFrame->getJointKeyFrames()) {
//		if (!m_model->hasJoint(p.first))
//			continue;
//		const auto& nextTransform = nf.at(p.first);
//		JointTransform currentTransform = m_model->getRestTransform(p.first);
//		auto interpolatedTransform = BoneTransform::interpolate(p.second, nextTransform, progression);
//		interpolatedTransform.translation += glm::vec3(currentTransform.x, currentTransform.y, 0.0f);
//		currentPose.insert(std::make_pair(p.first, interpolatedTransform.getLocalTransform()));
//	}
//	return currentPose;
//}
//
//
//void SkAnimator2::applyPoseToJoints(const std::unordered_map<std::string, glm::mat4> &currentPose,
//								   std::shared_ptr<Joint> joint, glm::mat4& parentTransform)
//{
//	// get the local transform of the current joint
//	glm::mat4 currentLocalTransform(1.0f);
//	if (currentPose.count(joint->getName()) > 0) {
//		currentLocalTransform = currentPose.at(joint->getName());
//
//	} else {
//		currentLocalTransform = joint->getRestTransform().getLocalTransform();
//	}
//	// mutliply by the parent
//	glm::mat4 currentTransform = parentTransform * currentLocalTransform;
//	// call children
//	for (const auto& c : joint->getChildren()) {
//		applyPoseToJoints(currentPose, c, currentTransform);
//	}
//	// revert to model space
//	//glm::mat4 ct = joint->getInverseBindTransform()*currentTransform;
//	glm::mat4 ct = currentTransform *joint->getInverseBindTransform();
//	joint->setAnimationTransform(ct);
//
//}
//
//void SkAnimator2::setModel(std::shared_ptr<IModel> model) {
//	m_model = std::dynamic_pointer_cast<SkModel>(model);
//	Start();
//	SetAnimation(m_model->getDefaultAnimation());
//
//}
//
//IModel* SkAnimator2::getModel() const {
//	return m_model.get();
//}
//
//std::type_index SkAnimator2::GetType() {
//	return std::type_index(typeid(IAnimator));
//}
//
//void SkAnimator2::SetAnimation(const std::string &anim, bool forward) {
//	if (m_animation == anim) {
//		return;
//	}
//	m_animation = anim;
//
//	m_currentAnimation = m_model->getAnimation(anim);
//	// m_animation = m_currentAnimId;
//	m_animationTime = 0.0f;
//	m_complete = false;
//}
//
//
