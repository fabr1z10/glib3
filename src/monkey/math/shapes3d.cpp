//#include <monkey/math/shapes/plane3d.h>
//#include <monkey/math/shapes/box3d.h>
//#include <monkey/error.h>
//
//// a plane3d always lies at y=0, you can only offset its x and z axes
//Plane3D::Plane3D(float width, float height, int plane, glm::vec3 offset) : Shape(offset), m_width(width), m_height(height), m_plane(plane)
//{
//    m_bounds.min = offset;
//    m_bounds.max = offset + glm::vec3(m_width, 0.0f, m_height);
//
//}
//
//Plane3D::Plane3D(const ITable & t) {
//    m_width = t.get<float>("width");
//    m_height = t.get<float>("height");
//	m_plane = t.get<int>("orientation");
//	//std::cout << ciappo;
//}
//
//void Plane3D::accept (AcyclicVisitor& v) {
//    Visitor<Plane3D>* v1 = dynamic_cast<Visitor<Plane3D>*>(&v);
//    if (v1 != 0)
//        v1->visit(*this);
//    else
//        GLIB_FAIL("not a Plane3D visitor");
//}
//
//bool Plane3D::isPointInside(glm::vec3 P) const {
//    return (P.x >= m_bounds.min.x && P.x <= m_bounds.max.x && P.z >= m_bounds.min.z && P.z <= m_bounds.max.z);
//}