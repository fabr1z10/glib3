#pragma once

#include <monkey/math/intersect.h>
#include <monkey/math/shapes/convexpoly.h>


CollisionReport performSAT(std::unordered_set<glm::vec2>& axesw, const Shape2D& a, const Shape2D& b, const glm::mat4& t1, const glm::mat4& t2);

CollisionReport SAT(const IConvexPolygon& p1, const IConvexPolygon& p2, const glm::mat4& t1, const glm::mat4& t2);
CollisionReport SATCircle(const IConvexPolygon& p, const Circle& c, const glm::mat4& t1, const glm::mat4& t2);
