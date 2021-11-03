#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <monkey/math/shapes/convexpoly.h>
#include <monkey/math/intersect.h>
#include <monkey/math/earcut.h>

// tests whether AB intersects CD
bool segmentIntersection(glm::vec2 A, glm::vec2 B, glm::vec2 C, glm::vec2 D, float& t, float& u);
int linint(glm::vec2 A, glm::vec2 B, glm::vec2 C, glm::vec2 D, float& t, float& u);

// Determines whether or not a set of three points is in counter-clockwise order.
bool triangleIsCCW(const glm::vec2& a, const glm::vec2& b, const glm::vec2& c);

// Test if point p lies inside ccw-specified convex n-gon given by vertices v[]
int pointInConvexPolygon(glm::vec2 p, const std::vector<glm::vec2>& v);

// helper method that projects a collection of points onto one axis
glm::vec2 project(const std::vector<glm::vec2>& points, const glm::vec2& axis, const glm::mat4& t);
CollisionReport circleVsCircle(const Circle& c1, const Circle& c2, const glm::mat4&, const glm::mat4&);

CollisionReport shapeVsCompound(const IShape& c1, const CompoundShape& c2, const glm::mat4&, const glm::mat4&);

//template<typename Vertex>
//std::vector<unsigned> triangulate(std::vector<Vertex>& vertices) {
//    using Coord = float;
//    using Point = std::array<Coord, 2>;
//    using N = uint32_t;
//    std::vector<std::vector<Point>> p;
//    std::vector<Point> points;
//    for (const auto& vertex : vertices) {
//        points.push_back({vertex.x, vertex.y});
//    }
//    p.push_back(points);
//    auto tri = mapbox::earcut<N>(p);
//    return tri;
//}
