#include <graph/visitor.h>
#include <graph/shape.h>
#include <graph/poly.h>
#include <graph/polyline.h>

class ShortestPath :
        public AcyclicVisitor,
        //public Visitor<Rect
        public Visitor<Polygon>,
        public Visitor<Poly>,
        public Visitor<PolyLine>
{
public:
    static std::vector<glm::vec2> Find(Shape&, glm::vec2 A, glm::vec2 B);
    //void visit(Rect&) override;
    void visit(Polygon&) override;
    void visit(Poly&) override;
    void visit(PolyLine&) override;
private:
    ShortestPath(glm::vec2 A, glm::vec2 B) : m_A{A}, m_B{B} {}
    glm::vec2 m_A, m_B;
    std::vector<glm::vec2> m_result;
};
