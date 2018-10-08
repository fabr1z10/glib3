#include <gfx/visitor.h>
#include <gfx/math/shape.h>
#include <gfx/math/poly.h>
#include <gfx/math/polyline.h>
#include <gfx/math/line.h>
#include <gfx/math/rect.h>
#include <gfx/math/circle.h>
#include <gfx/math/collisionreport.h>
#include <gfx/math/compound.h>

class RayCast2D :
        public AcyclicVisitor,
        //public Visitor<Rect
        public Visitor<Polygon>,
        public Visitor<Line>,
        public Visitor<Rect>,
        public Visitor<Circle>,
        public Visitor<CompoundShape>
{
public:
    RayCast2D (glm::vec2 O, glm::vec2 dir, float length, glm::mat4& t) : m_A(O), m_dir(dir), m_B(O + dir*length), m_transform(t), m_length(length) {}
    void visit(Polygon&) override;
    void visit(Line&) override;
    void visit(Rect&) override;
    void visit(Circle&) override;
    void visit(CompoundShape&) override;
    RayCastHit2D GetResult();
private:
    RayCastHit2D m_result;
    glm::mat4 m_transform;
    glm::vec2 m_A;
    glm::vec2 m_B;
    glm::vec2 m_dir;
    float m_length;
    float SegmentIntersection(glm::vec2 A, glm::vec2 B, glm::vec2 C, glm::vec2 D);
    RayCastHit2D SegmentIntersection(glm::vec2 A, glm::vec2 B, std::vector<glm::vec2>& p);
};


inline RayCastHit2D RayCast2D::GetResult() {
    return m_result;
}