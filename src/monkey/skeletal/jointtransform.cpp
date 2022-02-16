#include <monkey/skeletal/jointtransform.hpp>
#include <glm/gtx/transform.hpp>



JointTransform JointTransform::interpolate(const JointTransform &A, const JointTransform &B, float progression) {
	JointTransform t;
	t.scale = glm::mix (A.scale, B.scale, progression);
	t.rotation = glm::mix (A.rotation, B.rotation, progression);
	t.translation = glm::mix(A.translation, B.translation, progression);
	return t;
}

glm::mat4 JointTransform::getLocalTransform() const {
	auto sc = glm::scale(scale);
	auto rot =glm::mat4_cast(rotation);
	auto trans = glm::translate(glm::mat4(1.0f), translation);
	//return rot * trans;
	return trans*rot;
}

glm::mat4 JointTransform::getLocalTransformScale() const {
    auto sc = glm::scale(scale);
    auto rot =glm::mat4_cast(rotation);
    auto trans = glm::translate(glm::mat4(1.0f), translation);
    //return rot * trans;
    return trans*rot*sc;
}


JointTransform& JointTransform::operator+=(const JointTransform &b) {
	translation += b.translation;
	rotation = b.rotation;
	scale *= b.scale;
//    x += b.x;
//    y += b.y;
//    alpha += b.alpha;
    return *this;

}