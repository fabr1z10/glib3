#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>


class BoneTransform {
public:
	BoneTransform() ;
	glm::vec3 translation;
	glm::quat rotation;

	static BoneTransform interpolate(const BoneTransform& A, const BoneTransform& B, float progression);

	// converts to matrix
	glm::mat4 getLocalTransform() const;
};