//#include <algorithm>
//#include <monkey/math/compound.h>
//#include <monkey/error.h>
//
//bool CompoundShape::isPointInside(glm::vec3 P) const {
//    for (auto& shape : m_shapes) {
//        if (shape->isPointInside(P))
//            return true;
//    }
//    return false;
//}
//
//void CompoundShape::accept (AcyclicVisitor& v) {
//    Visitor<CompoundShape>* v1 = dynamic_cast<Visitor<CompoundShape>*>(&v);
//    if (v1 != 0)
//        v1->visit(*this);
//    else
//        GLIB_FAIL("not a compound shape visitor");
//}
//
//
//std::string CompoundShape::toString() const {
//    std::stringstream stream;
//    stream << "Compound shape with " << m_shapes.size() << " shapes";
//    return stream.str();
//}
//
//glm::vec2 CompoundShape::project(const glm::vec2 axis, const glm::mat4& worldTransform) {
//    return glm::vec2(0.0f);
//}
//
//std::vector<glm::vec2> CompoundShape::getPoints() {
//    return std::vector<glm::vec2>();
//}
//
//std::vector<glm::vec2> CompoundShape::getEdges(){
//    return std::vector<glm::vec2>();
//}
//
//void CompoundShape::AddShape (std::shared_ptr<Shape> s) {
//    m_shapes.push_back(s);
//    // update the bounding box
//    auto b = s->getBounds();
//    if (m_shapes.size() == 1) {
//        m_bounds = b;
//    } else {
//        m_bounds.min.x = std::min(m_bounds.min.x, b.min.x);
//        m_bounds.min.y = std::min(m_bounds.min.y, b.min.y);
//        m_bounds.max.x = std::max(m_bounds.max.x, b.max.x);
//        m_bounds.max.y = std::max(m_bounds.max.y, b.max.y);
//    }
//}
