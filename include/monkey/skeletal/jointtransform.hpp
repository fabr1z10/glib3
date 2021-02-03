#pragma once

#include <glm/glm.hpp>
#include <monkey/math/geom.h>
#include <glm/gtc/quaternion.hpp>

struct JointTransform {
    JointTransform () : translation(glm::vec3(0.0f)), rotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)), scale(glm::vec3(1.0f)) {}

    // remember, this position and rotation are relative to the parent bone!
    glm::vec3 translation;
	glm::quat rotation;
	glm::vec3 scale;

    // comp assignment
    JointTransform& operator+=(const JointTransform& b);

    static JointTransform interpolate(const JointTransform& A, const JointTransform& B, float progression);
    glm::mat4 getLocalTransform() const;
};