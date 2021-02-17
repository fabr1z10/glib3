//#include "monkey/math/shapes/surf2d.h"
//
//ISurf2D::ISurf2D(const ITable & t) {
//    m_min = t.get<glm::vec2>("min");
//    m_gridSize = t.get<glm::vec2>("grid_size");
//    m_nx = t.get<int>("nx");
//    m_ny = t.get<int>("ny");
//
//
//
//}
//
//void ISurf2D::accept (AcyclicVisitor& v) {
//    auto v1 = dynamic_cast<Visitor<ISurf2D>*>(&v);
//    if (v1 != 0)
//        v1->visit(*this);
//    else
//    GLIB_FAIL("not a Box3D visitor");
//}
//
//int ISurf2D::getPointCount() const {
//    return m_nx * m_ny;
//
//}
//
//PySurf2D::PySurf2D(const ITable & t) : ISurf2D(t) {
//
//    m_func = t.get<pybind11::function>("func");
//
//}
//
//float PySurf2D::operator()(float x, float y) {
//    return m_func(x, y).cast<float>();
//
//}