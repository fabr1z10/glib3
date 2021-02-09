#include <monkey/skeletal/joint.hpp>


Joint::Joint(int index, const std::string& name) : m_index(index), m_localBindTransform(1.0f),
    m_inverseBindTransform(1.0f), m_name(name), m_bindTransform(1.0f), m_z(0) {}


Joint::Joint(int index, const std::string& name, float z) :
    m_index(index), m_name(name), m_root(true), m_localBindTransform(1.0f), m_inverseBindTransform(1.0f), m_bindTransform(1.0f), m_z(z)
{
    // bind and inverse bind transforms are initialized to identity
    m_inverseBindTransform[3][2] = m_z;

    //, m_localTransform(localTransform), m_parent(parent) {
    //m_localBindTransform = localTransform.getLocalTransform();
}


void Joint::setParent(const std::string &parent, const std::string &attachPoint) {
    m_root = false;
    m_parent = parent;
    m_attachPoint = attachPoint;
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

void Joint::setLocalToParentTransform(const JointTransform &t, const glm::mat4& parentBindTransform) {
    m_localTransform = t;
    m_localBindTransform = m_localTransform.getLocalTransform();
    //m_localBindTransform[3][2] = m_z;
    m_bindTransform = parentBindTransform * m_localBindTransform;
    m_inverseBindTransform = glm::inverse(m_bindTransform);
    m_inverseBindTransform[3][2]=m_z;
}

void Joint::setAnimationTransform(glm::mat4 animationTransform) {

    m_transform = animationTransform;
}

void Joint::calcInverseBindTransform(glm::mat4 parentBindTransform) {

    glm::mat4 bindTransform = parentBindTransform * m_localBindTransform ;
    m_inverseBindTransform = glm::inverse(bindTransform);
    m_inverseBindTransform[3][2]=m_z;

    for (const auto& child : m_children) {
        child->calcInverseBindTransform(bindTransform);
    }
}