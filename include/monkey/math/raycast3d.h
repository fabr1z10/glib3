#include <monkey/math/raycast2d.h>
//#include <monkey/visitor.h>
//#include <monkey/math/collisionreport.h>
//#include <monkey/math/shapes/plane3d.h>
//#include <monkey/math/shapes/box3d.h>
//

class RayCast3D : public IRayCast {
public:
	RayCast3D();

	RayCastHit run(glm::vec3 O, glm::vec3 dir, float length, IShape *shape, const glm::mat4 &t) override;
private:
	std::unordered_map<ShapeType, std::function<RayCastHit(glm::vec3, glm::vec3, IShape*, const glm::mat4&)>> m_raycasters;
	RayCastHit rayVsAABB(glm::vec3 O, glm::vec3 dir, IShape* aabb, const glm::mat4&);
	//float getT(float p, float o, float r);
};

/*inline float RayCast3D::getT(float p, float o, float r) {
	if (r == 0.0f) {
		return std::numeric_limits<float>::infinity();
	}
	return (p - o) / r;
}*/
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