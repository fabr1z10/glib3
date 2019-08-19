#include <gfx/visitor.h>
#include <gfx/math/shape.h>
#include <gfx/math/poly.h>
#include <gfx/math/polyline.h>


class ClosestPointOnEdge :
    public AcyclicVisitor,
    //public Visitor<Rect>,
    public Visitor<Polygon>,
    public Visitor<Poly>,
    public Visitor<PolyLine>
{
public:
    static glm::vec2 Find(Shape&, glm::vec2 P);
    //void visit(Rect&) override;
    void visit(Polygon&) override;
    void visit(Poly&) override;
    void visit(PolyLine&) override;
    //void visit(Poly&) override;
private:
    // returns the closest point
    glm::vec2 getNearest(Polygon&, glm::mat4& t, float&, glm::vec2 closestPointSoFar);
    ClosestPointOnEdge(glm::vec2 P) : m_P{P} {}
    glm::vec2 m_P;
    glm::vec2 m_result;
};
