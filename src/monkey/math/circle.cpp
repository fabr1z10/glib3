#include <monkey/math/circle.h>
#include <monkey/error.h>

Circle::Circle(const ITable& t) : Shape(t) {
    m_radius = t.get<float>("radius");
    m_bounds.min = m_offset - glm::vec3(m_radius, m_radius, 1.0f);
    m_bounds.max = m_offset + glm::vec3(m_radius, m_radius, 1.0f);

}

bool Circle::isPointInside(glm::vec3 P) const {
    glm::vec2 rp = P - m_offset;
    return (rp.x * rp.x + rp.y * rp.y <= m_radius * m_radius);
}

void Circle::accept (AcyclicVisitor& v) {
    Visitor<Circle>* v1 = dynamic_cast<Visitor<Circle>*>(&v);
    if (v1 != 0)
        v1->visit(*this);
    else
        GLIB_FAIL("not a circle visitor");
}


std::string Circle::toString() const {
    std::stringstream stream;
    stream << "Circle (radius = " << m_radius << ")";
    return stream.str();
}

glm::vec2 Circle::project(const glm::vec2 axis, const glm::mat4& worldTransform) {
    float x = glm::dot(glm::vec2(worldTransform * glm::vec4(m_offset, 1.0f)), axis);
    return glm::vec2(x-m_radius, x+ m_radius);
}


std::vector<glm::vec2> Circle::getPoints() {
    return { m_offset };
}


std::vector<glm::vec2> Circle::getEdges() {
    return {};
}
