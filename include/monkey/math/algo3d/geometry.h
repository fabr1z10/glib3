#pragma once

#include <monkey/math/collisionreport.h>
#include <monkey/math/shapes3d/plane.h>
#include <monkey/math/shapes3d/segment3d.h>


// 3d tests
CollisionReport intersectSegmentPlane(const Segment3D& s, const Plane& p); //, float &t, glm::vec3 &q);