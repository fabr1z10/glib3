#pragma once

//#include <monkey/visitor.h>
#include <monkey/singleton.h>
#include <monkey/math/shape.h>
//#include <monkey/math/shapes/poly.h>
//#include <monkey/math/shapes/polyline.h>
//#include "monkey/math/shapes/rect.h"
#include <glm/glm.hpp>
//
//struct ClosestPointResult {
//    glm::vec2 P;
//    glm::vec2 normal;
//};
//
class ClosestPointOnEdge : public Singleton<ClosestPointOnEdge>
{
    friend class Singleton<ClosestPointOnEdge>;
public:
    glm::vec2 find(glm::vec2 P, const IShape*);
//    static ClosestPointResult Find(Shape&, glm::vec2 P);
//    void visit(Rect&) override;
//    void visit(Polygon&) override;
//    void visit(Poly&) override;
//    void visit(PolyLine&) override;
//    //void visit(Poly&) override;
private:
    ClosestPointOnEdge();
    std::unordered_map<ShapeType, std::function<glm::vec2(glm::vec2, const IShape*)>> m_algos;
	void getClosestPointToOutline(const std::vector<glm::vec2>& vertices, const glm::vec2 P, glm::vec2& current, float& currDist, bool hole);
    float m_eps;
    glm::vec2 findCircle(glm::vec2, const IShape*);
    glm::vec2 findPoly (glm::vec2, const IShape*);
//    void replace(float& bestd, glm::vec2& bp, float cand, glm::vec2 bc);
//    // returns the closest point
//    void getNearest(Polygon&, float&, glm::vec2& closestPointSoFar, glm::vec2 offset = glm::vec2(0.0f), bool flip = false);
//    ClosestPointOnEdge(glm::vec2 P) : m_P{P} {}
//    glm::vec2 m_P;
//    // normal pointing INSIDE
//    glm::vec2 m_normal;
//    glm::vec2 m_result;
};
