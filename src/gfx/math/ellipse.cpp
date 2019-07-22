#include "gfx/math/ellipse.h"
#include "gfx/error.h"

bool Ellipse::isPointInside(glm::vec3 P) const {
    glm::vec3 rp = P - m_offset;
    // ellipse satisfies equation
    // x^2 / r_x^2 + y^2 / r_y^2 \leq 1
    
    return (rp.x * rp.x / (m_xSemiAxis * m_xSemiAxis) + rp.y * rp.y / (m_ySemiAxis* m_ySemiAxis) <= 1.0f);
}

void Ellipse::accept (AcyclicVisitor& v) {
    Visitor<Ellipse>* v1 = dynamic_cast<Visitor<Ellipse>*>(&v);
    if (v1 != 0)
        v1->visit(*this);
    else
        GLIB_FAIL("not an ellipse visitor.");
}


std::string Ellipse::toString() const {
    std::stringstream stream;
    stream << "Ellipse (axes = (" << m_xSemiAxis << ", " << m_ySemiAxis << "))";
    return stream.str();
}

glm::vec2 Ellipse::project(const glm::vec2 axis, const glm::mat4& worldTransform) {
    throw ;
}


std::vector<glm::vec2> Ellipse::getPoints() {
    return { m_offset };
}


std::vector<glm::vec2> Ellipse::getEdges() {
    return {};
}

