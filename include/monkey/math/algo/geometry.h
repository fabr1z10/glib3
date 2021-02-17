#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <monkey/math/shapes/convexpoly.h>
#include <monkey/math/intersect.h>

// Determines whether or not a set of three points is in counter-clockwise order.
bool triangleIsCCW(const glm::vec2& a, const glm::vec2& b, const glm::vec2& c);

// Test if point p lies inside ccw-specified convex n-gon given by vertices v[]
int pointInConvexPolygon(glm::vec2 p, const std::vector<glm::vec2>& v);

// helper method that projects a collection of points onto one axis
glm::vec2 project(const std::vector<glm::vec2>& points, const glm::vec2& axis);
CollisionReport circleVsCircle(const Circle& c1, const Circle& c2);
