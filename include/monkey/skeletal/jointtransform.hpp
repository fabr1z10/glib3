#pragma once

#include <glm/glm.hpp>
#include <monkey/math/geom.h>

struct JointTransform {
    JointTransform () : x(0.0f), y(0.0f), alpha(0.0f) {}

    // remember, this position and rotation are relative to the parent bone!
    JointTransform (float x, float y, float angleDeg) : x(x), y(y), alpha(deg2rad * angleDeg) {}

    float x;
    float y;

    // the angle in radians
    float alpha;

    // adding scalex and scaley ?

    // comp assignment
    JointTransform& operator+=(const JointTransform& b);


    static JointTransform interpolate(const JointTransform& A, const JointTransform& B, float progression);
    glm::mat4 getLocalTransform() const;
};