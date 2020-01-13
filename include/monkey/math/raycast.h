#include <monkey/visitor.h>
#include <monkey/math/shape.h>
#include <monkey/math/poly.h>
#include <monkey/math/polyline.h>
#include <monkey/math/line.h>
#include <monkey/math/rect.h>
#include <monkey/math/circle.h>
#include <monkey/math/collisionreport.h>
#include <monkey/math/compound.h>
#include <monkey/math/plane3d.h>
#include <monkey/math/box.h>

class RayCast2D :
        public AcyclicVisitor,
        //public Visitor<Rect
        public Visitor<Polygon>,
        public Visitor<Poly>,
        public Visitor<Line>,
        public Visitor<Rect>,
        public Visitor<Circle>,
        public Visitor<CompoundShape>,
        public Visitor<Plane3D>,
    public Visitor<Box>

{
public:
    RayCast2D (glm::vec3 O, glm::vec3 dir, float length, glm::mat4& t) :
        m_A(O), m_dir(dir), m_B(O + dir*length), m_transform(t), m_length(length) {}
    void visit(Polygon&) override;
    void visit(Poly&) override;
    void visit(Line&) override;
    void visit(Rect&) override;
    void visit(Circle&) override;
    void visit(CompoundShape&) override;
    void visit(Plane3D&) override;
    void visit(Box&) override;

RayCastHit GetResult();
private:
    RayCastHit m_result;
    glm::mat4 m_transform;
    glm::vec3 m_A;              // tail point
    glm::vec3 m_B;              // head point
    glm::vec3 m_dir;            // direction (unit vector)
    float m_length;
    float SegmentIntersection(glm::vec2 A, glm::vec2 B, glm::vec2 C, glm::vec2 D);
    RayCastHit SegmentIntersection(glm::vec2 A, glm::vec2 B, std::vector<glm::vec2>& p);
    RayCastHit SegmentIntersectionSimple(glm::vec2 A, glm::vec2 B, std::vector<glm::vec2>& p);

};


inline RayCastHit RayCast2D::GetResult() {
    return m_result;
}