//#include <monkey/visitor.h>
//#include <monkey/math/collisionreport.h>
//#include <monkey/math/shapes/plane3d.h>
//#include <monkey/math/shapes/box3d.h>
//
//class RayCast3D :
//    public AcyclicVisitor,
//    public Visitor<Plane3D>,
//    public Visitor<Box3D>
//    // public Visitor<Poly3D>
//{
//public:
//    RayCast3D (glm::vec3 O, glm::vec3 dir, float length, glm::mat4& t) : m_A(O), m_dir(dir), m_B(O + dir*length), m_transform(t), m_length(length) {}
//    void visit(Plane3D&) override;
//    void visit(Box3D&) override;
//
//    RayCastHit GetResult();
//private:
//    RayCastHit m_result;
//    glm::mat4 m_transform;
//    glm::vec3 m_A;
//    glm::vec3 m_B;
//    glm::vec3 m_dir;
//    float m_length;
//};
//
//
//inline RayCastHit RayCast3D::GetResult() {
//    return m_result;
//}