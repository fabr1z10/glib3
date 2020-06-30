#define GLM_ENABLE_EXPERIMENTAL

#include <monkey/skeletal/jointtransform.hpp>
#include <glm/gtx/transform.hpp>



JointTransform JointTransform::interpolate(const JointTransform &A, const JointTransform &B, float progression) {
    JointTransform t;
    t.x = A.x + (B.x - A.x) * progression;
    t.y = A.y + (B.y - A.y) * progression;
    t.alpha = A.alpha + (B.alpha - A.alpha) * progression;
    return t;

}

glm::mat4 JointTransform::getLocalTransform() const {
    glm::mat4 r = glm::rotate(alpha, glm::vec3(0, 0, 1));
    r[3][0] = x;
    r[3][1] = y;
    return r;
}

JointTransform& JointTransform::operator+=(const JointTransform &b) {
    x += b.x;
    y += b.y;
    alpha += b.alpha;
    return *this;

}