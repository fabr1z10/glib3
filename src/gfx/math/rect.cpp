#include "gfx/math/rect.h"
#include <gfx/error.h>
#include "gfx/math/geomalgo.h"

bool Rect::isPointInside(glm::vec3 P) const {
    // ignore z coord
    P -= m_offset;
    return !(P.x < 0 || P.x > m_width || P.y < 0 || P.y > m_height);
}

void Rect::accept (AcyclicVisitor& v) {
    Visitor<Rect>* v1 = dynamic_cast<Visitor<Rect>*>(&v);
    if (v1 != 0)
        v1->visit(*this);
    else
        GLIB_FAIL("not a rect visitor");
}


std::string Rect::toString() const {
    std::stringstream stream;
    stream << "Rect (width = " << m_width << ", height = " << m_height << ")";
    return stream.str();
}

glm::vec2 Rect::project(const glm::vec2 axis, const glm::mat4& worldTransform) {
    std::vector<glm::vec2> points = {
            {m_offset.x, m_offset.y},
            {m_offset.x+m_width, m_offset.y},
            {m_offset.x, m_offset.y + m_height},
            {m_offset.x+m_width, m_offset.y+m_height}
    };
    return Projection(points, axis, worldTransform);
}


std::vector<glm::vec2> Rect::getPoints() {
    return {
            {m_offset.x, m_offset.y},
            {m_offset.x + m_width, m_offset.y},
            {m_offset.x + m_width, m_offset.y + m_height},
            {m_offset.x, m_offset.y + m_height}
    };
}


std::vector<glm::vec2> Rect::getEdges() {
    return { glm::vec2(m_width, 0.0), glm::vec2(0.0, m_height)};
}
