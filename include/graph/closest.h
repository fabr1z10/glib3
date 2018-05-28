#include <graph/visitor.h>
#include <graph/shape.h>
#include <graph/poly.h>

class ClosestPointOnEdge :
    public AcyclicVisitor,
    //public Visitor<Rect>,
    public Visitor<Polygon>,
    public Visitor<Poly>
{
public:
    static glm::vec2 Find(Shape&, glm::vec2 P);
    //void visit(Rect&) override;
    void visit(Polygon&) override;
    void visit(Poly&) override;
    //void visit(Poly&) override;
private:

    glm::vec2 getNearest(Polygon&, float&, glm::vec2 closestPointSoFar);
    ClosestPointOnEdge(glm::vec2 P) : m_P{P} {}
    glm::vec2 m_P;
    glm::vec2 m_result;
};
