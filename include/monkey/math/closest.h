#include <monkey/visitor.h>
#include <monkey/math/shape.h>
#include <monkey/math/poly.h>
#include <monkey/math/polyline.h>
#include "rect.h"
#include <glm/glm.hpp>

struct ClosestPointResult {
    glm::vec2 P;
    glm::vec2 normal;
};

class ClosestPointOnEdge :
    public AcyclicVisitor,
    public Visitor<Rect>,
    public Visitor<Polygon>,
    public Visitor<Poly>,
    public Visitor<PolyLine>
{
public:
    static ClosestPointResult Find(Shape&, glm::vec2 P);
    void visit(Rect&) override;
    void visit(Polygon&) override;
    void visit(Poly&) override;
    void visit(PolyLine&) override;
    //void visit(Poly&) override;
private:
    void replace(float& bestd, glm::vec2& bp, float cand, glm::vec2 bc);
    // returns the closest point
    void getNearest(Polygon&, float&, glm::vec2& closestPointSoFar, glm::vec2 offset = glm::vec2(0.0f), bool flip = false);
    ClosestPointOnEdge(glm::vec2 P) : m_P{P} {}
    glm::vec2 m_P;
    // normal pointing INSIDE
    glm::vec2 m_normal;
    glm::vec2 m_result;
};
