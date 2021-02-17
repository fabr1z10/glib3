//#include <monkey/math/shapes/polychain3d.h>
//
//
//
//PolyChain3D::PolyChain3D(const ITable & t) {
//    m_width = t.get<float>("width");
//    m_points = t.get<std::vector<float>> ("points");
//
//}
//
//void PolyChain3D::accept (AcyclicVisitor& v) {
//    auto v1 = dynamic_cast<Visitor<PolyChain3D>*>(&v);
//    if (v1 != 0)
//        v1->visit(*this);
//    else
//    GLIB_FAIL("not a Plane3D visitor");
//}
//
//float PolyChain3D::width() const {
//    return m_width;
//}
//
//size_t PolyChain3D::getPointCount() const {
//    return m_points.size() / 2;
//}
//
//glm::vec2 PolyChain3D::getPoint (size_t i) const {
//    return glm::vec2(m_points[2*i], m_points[2*i+1]);
//}