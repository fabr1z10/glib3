#include <monkey/skeletal/joint.hpp>

Joint::Joint(int index, std::string name, JointTransform localTransform) : m_index(index), m_name(name), m_localTransform(localTransform) {
    m_localBindTransform = localTransform.getLocalTransform();


}
void Joint::addChild(std::shared_ptr<Joint> child) {
    m_children.push_back(child);
}

glm::mat4 Joint::getAnimatedTransform() {

    return m_transform;
}

void Joint::setRest() {
    m_transform = glm::mat4(1.0f);
    for (const auto& c : m_children) {
        c->setRest();
    }

}

void Joint::setAnimationTransform(glm::mat4 animationTransform) {

    m_transform = animationTransform;
}

void Joint::calcInverseBindTransform(glm::mat4 parentBindTransform) {

    glm::mat4 bindTransform = parentBindTransform * m_localBindTransform ;
    m_inverseBindTransform = glm::inverse(bindTransform);
    for (const auto& child : m_children) {
        child->calcInverseBindTransform(bindTransform);
    }
}