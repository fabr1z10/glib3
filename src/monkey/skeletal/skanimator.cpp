#include <monkey/skeletal/skanimator.hpp>
#include <glm/gtx/transform.hpp>

SkAnimator::SkAnimator(std::shared_ptr<IModel> model) : IAnimator(), m_currentAnimation(nullptr), m_complete(false), m_speedUp(1.0f)
{
    m_model = std::dynamic_pointer_cast<SkModel>(model);
    m_initAnim = m_model->GetDefaultAnimation();

}



void SkAnimator::Update(double dt) {

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
    applyPoseToJoints (currentPose, m_model->getRootJoint(), I);

    // apply offset
    const auto& offsetPoints = m_model->getOffsetPoints();
    if (!offsetPoints.empty()) {
        glm::vec3 offset(0.0f);
        //std::cout << "no of offset points: " << offsetPoints.size() << "\n";
        for (const auto &a : offsetPoints) {

            // find coordinates of offset pointg
            glm::mat4 t = m_model->getJoint(a.first)->getAnimatedTransform();
            glm::vec4 p = t * glm::vec4(a.second, 1.0f);
            offset.y = std::max(-p.y, offset.y);
        }
        //std::cerr << offset.y << "\n";
        m_renderer->SetTransform(glm::translate(offset));
    }

}

/**
 * This method returns the current animation pose of the entity. It returns
 * the desired ***local-space*** transforms for all the joints in a map, indexed
 * by the name of the joint that they correspond to.
 *
 * The pose is calculated based on the previous and next keyframes in the
 * current animation. Each keyframe provides the desired pose at a certain
 * time in the animation, so the animated pose for the current time can be
 * calculated by interpolating between the previous and next keyframe.
 *
 * This method first finds the preious and next keyframe, calculates how far
 * between the two the current animation is, and then calculated the pose
 * for the current animation time by interpolating between the transforms at
 * those keyframes.
 *
 * @return The current pose as a map of the desired local-space transforms
 *         for all the joints. The transforms are indexed by the name ID of
 *         the joint that they should be applied to.
 */
std::unordered_map<std::string, JointTransform> SkAnimator::calculateCurrentAnimationPose() {
    auto frames = m_currentAnimation->getPreviousAndNextKeyFrames(m_animationTime);
    m_currentIndex = std::get<0>(frames)->getIndex();
//    float totalTime = frames.second->getTimeStamp() - frames.first->getTimeStamp();
//    float currentTime = m_animationTime - frames.first->getTimeStamp();
//    float progression = (totalTime == 0.0f) ? 0.0f : (currentTime / totalTime);
    return interpolatePoses(std::get<0>(frames), std::get<1>(frames), std::get<2>(frames));
}

/**
 * Finds the previous keyframe in the animation and the next keyframe in the
 * animation, and returns them in an array of length 2. If there is no
 * previous frame (perhaps current animation time is 0.5 and the first
 * keyframe is at time 1.5) then the first keyframe is used as both the
 * previous and next keyframe. The last keyframe is used for both next and
 * previous if there is no next keyframe.
 *
 * @return The previous and next keyframes, in an array which therefore will
 *         always have a length of 2.
 */
//std::pair<SKeyFrame*, SKeyFrame*> SkAnimator::getPreviousAndNextFrames() {
//
//    const auto& allFrames = m_currentAnimation->getKeyFrames();
//    SKeyFrame* previousFrame = allFrames[0].get();
//    SKeyFrame* nextFrame = allFrames[0].get();
//    for (int i = 1; i < allFrames.size(); i++) {
//        nextFrame = allFrames[i].get();
//        if (nextFrame->getTimeStamp() > m_animationTime) {
//            break;
//        }
//        previousFrame = allFrames[i].get();
//    }
//    return std::make_pair(previousFrame, nextFrame);
//}

/**
 * Calculates all the local-space joint transforms for the desired current
 * pose by interpolating between the transforms at the previous and next
 * keyframes.
 *
 * @param previousFrame
 *            - the previous keyframe in the animation.
 * @param nextFrame
 *            - the next keyframe in the animation.
 * @param progression
 *            - a number between 0 and 1 indicating how far between the
 *            previous and next keyframes the current animation time is.
 * @return The local-space transforms for all the joints for the desired
 *         current pose. They are returned in a map, indexed by the name of
 *         the joint to which they should be applied.
 */
std::unordered_map<std::string, JointTransform> SkAnimator::interpolatePoses(SKeyFrame* previousFrame, SKeyFrame* nextFrame, float progression) {
    std::unordered_map<std::string, JointTransform> currentPose;
    const auto& nf = nextFrame->getJointKeyFrames();
    for (const auto& p : previousFrame->getJointKeyFrames()) {
    	Joint* currentJoint = m_model->getJoint(p.first);
        if (currentJoint == nullptr) {
			continue;
		}

        // previousTransform is p.second
        JointTransform nextTransform = nf.at(p.first);
        JointTransform currentTransform = m_model->getRestTransform(p.first);

        currentTransform += JointTransform::interpolate(p.second, nextTransform, progression);
        //currentTransform.z = 0;
        //std::cout << m_animationTime << " . " << currentTransform.alpha << "\n";
        currentPose.insert(std::make_pair(p.first, currentTransform));
    }
    return currentPose;
}



void SkAnimator::Start() {
    m_animationTime = 0.0f;
    if (!m_initAnim.empty()) {
        SetAnimation(m_initAnim);
    }
    m_renderer = m_entity->GetComponent<Renderer>();
}

std::unordered_map<std::string, glm::mat4> SkAnimator::computePose(const std::string &animation, float t) {
    auto* anim = m_model->getAnimation(animation);
    const auto& keyFrames = anim->getKeyFrames();
    unsigned i = 1;
    float k = 0.0f;
    auto fr = anim->getPreviousAndNextKeyFrames(t);
//    for (; i< keyFrames.size(); ++i) {
//        float t1 = keyFrames[i]->getTimeStamp();
//        if (t1 >= t) {
//            float t0 = keyFrames[i-1]->getTimeStamp();
//            k = (t - t0) / (t1 - t0);
//            break;
//        }
//    }
    auto cpose = interpolatePoses(std::get<0>(fr), std::get<1>(fr), std::get<2>(fr));
    std::list<std::pair<std::shared_ptr<Joint>, glm::mat4>> joints;
    joints.emplace_back(m_model->getRootJoint(), glm::mat4(1.0f));
    std::unordered_map<std::string, glm::mat4> output;
    while (!joints.empty()) {
        auto currentJointData = joints.front();
        auto currentJoint = currentJointData.first;
        auto parentTransform = currentJointData.second;
        joints.pop_front();
        glm::mat4 currentLocalTransform(1.0f);
        auto iter = cpose.find(currentJoint->getName());
        if (iter != cpose.end()) {
            currentLocalTransform = iter->second.getLocalTransform();
        } else {
            currentLocalTransform = currentJoint->getRestTransform().getLocalTransform();
        }
        glm::mat4 currentTransform = parentTransform * currentLocalTransform;
        // push children
        for (const auto& c : currentJoint->getChildren()) {
            joints.emplace_back(c, currentTransform);
        }
        output[currentJoint->getName()] = currentTransform;
    }
    return output;
}



void SkAnimator::SetAnimation(const std::string &anim, bool forward) {
    if (m_animation == anim) {
        return;
    }
    m_animation = anim;

    m_currentAnimation = m_model->getAnimation(anim);
    // m_animation = m_currentAnimId;
    m_animationTime = 0.0f;
    m_complete = false;
}

void SkAnimator::setSpeedUp(float value) {
    m_speedUp = value;
}

void SkAnimator::setModel(std::shared_ptr<IModel> model) {
    m_model = std::dynamic_pointer_cast<SkModel>(model);
    Start();
    SetAnimation(m_model->GetDefaultAnimation());

}

IModel* SkAnimator::getModel() const {
    return m_model.get();
}

std::type_index SkAnimator::GetType() {
    return std::type_index(typeid(IAnimator));
}


bool SkAnimator::IsComplete() const {
    return m_complete;
}



void SkAnimator::applyPoseToJoints(const std::unordered_map<std::string, JointTransform> &currentPose,
                                   std::shared_ptr<Joint> joint, glm::mat4& parentTransform)
{
    // get the local transform of the current joint
    glm::mat4 currentLocalTransform(1.0f);
    glm::mat4 scalingMatrix (1.0f);
    if (currentPose.count(joint->getName()) > 0) {
        currentLocalTransform = currentPose.at(joint->getName()).getLocalTransform();
        scalingMatrix = glm::scale(glm::vec3(currentPose.at(joint->getName()).scale));
    } else {
        currentLocalTransform = joint->getRestTransform().getLocalTransform();
    }
    // mutliply by the parent
    glm::mat4 currentTransform = parentTransform * currentLocalTransform;

    // call children

    for (const auto& c : joint->getChildren()) {
		// remove scale by current transform
        applyPoseToJoints(currentPose, c, currentTransform);
    }
    // apply scale
    glm::mat4 scaledCurrentTransform = currentTransform * scalingMatrix;
    // revert to model space
    //glm::mat4 ct = joint->getInverseBindTransform()*currentTransform;
    glm::mat4 ct = scaledCurrentTransform *joint->getInverseBindTransform();
    joint->setAnimationTransform(ct);
	//std::cerr << "setting " << joint->getName() << " to " << ct[3][0] << ", " << ct[3][1] << "\n";
}