#include <monkey/math/shapes/circle.h>
#include <monkey/error.h>


Circle::Circle(float radius, glm::vec3 offset) : Shape2D(), m_radius(radius) {
    m_offset = offset;
    m_bounds.min = offset - glm::vec3(m_radius, m_radius, 1.0f);
    m_bounds.max = offset + glm::vec3(m_radius, m_radius, 1.0f);
}

Circle::Circle(const ITable& t) : Shape2D(t) {
    m_radius = t.get<float>("radius");
    m_bounds.min = m_offset - glm::vec3(m_radius, m_radius, 1.0f);
    m_bounds.max = m_offset + glm::vec3(m_radius, m_radius, 1.0f);

}

bool Circle::isPointInside(glm::vec3 P) const {
    glm::vec2 rp = P - m_offset;
    return (rp.x * rp.x + rp.y * rp.y <= m_radius * m_radius);
}

std::unique_ptr<IShape> Circle::transform(const glm::mat4 &t) {
    glm::vec2 center = t * glm::vec4(m_offset, 1.0f);
    return std::make_unique<Circle>(m_radius, glm::vec3(center, 0.0f));
}
//
//void Circle::accept (AcyclicVisitor& v) {
//    Visitor<Circle>* v1 = dynamic_cast<Visitor<Circle>*>(&v);
//    if (v1 != 0)
//        v1->visit(*this);
//    else
//        GLIB_FAIL("not a circle visitor");
//}
//
//
//std::string Circle::toString() const {
//    std::stringstream stream;
//    stream << "Circle (radius = " << m_radius << ")";
//    return stream.str();
//}
//
glm::vec2 Circle::project(glm::vec2 axis) const {
    float x = glm::dot(glm::vec2(m_offset), axis);
    return glm::vec2(x - m_radius, x + m_radius);
}
//
//
//std::vector<glm::vec2> Circle::getPoints() {
//    return { m_offset };
//}
//
//
//std::vector<glm::vec2> Circle::getEdges() {
//    return {};
//}
