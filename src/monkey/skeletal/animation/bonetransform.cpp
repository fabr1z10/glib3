//#include <monkey/skeletal/animation/bonetransform.hpp>
//
//// initialize to 0 translation and identity quat
//BoneTransform::BoneTransform() : translation(glm::vec3(0.0f)), rotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f))
//{}
//
//BoneTransform BoneTransform::interpolate(const BoneTransform &A, const BoneTransform &B, float progression) {
//	BoneTransform t;
//	t.rotation = glm::mix (A.rotation, B.rotation, progression);
//	t.translation = glm::mix(A.translation, B.translation, progression);
//	return t;
//}
//
//glm::mat4 BoneTransform::getLocalTransform() const {
//	return glm::mat4_cast(rotation);
//}