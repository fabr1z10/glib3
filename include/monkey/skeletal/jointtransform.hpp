#pragma once

#include <glm/glm.hpp>

struct JointTransform {
    float x;
    float y;
    float alpha;

    static JointTransform interpolate(const JointTransform& A, const JointTransform& B, float progression);
    glm::mat4 getLocalTransform() const;
};