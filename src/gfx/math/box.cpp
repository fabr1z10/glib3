#include <gfx/math/box.h>
#include <gfx/error.h>
#include <gfx/visitor.h>

Box::Box(float width, float height, float depth) : Shape(), m_width(width), m_height(height), m_depth(depth) {
    m_bounds.min = glm::vec3(0.0f, 0.0f, 0.f);
    m_bounds.max = glm::vec3(m_width, m_height, m_depth);
}

void Box::accept (AcyclicVisitor& v) {
    Visitor<Box>* v1 = dynamic_cast<Visitor<Box>*>(&v);
    if (v1 != 0)
        v1->visit(*this);
    else
        GLIB_FAIL("not a Box visitor");
}

bool Box::isPointInside(glm::vec3 P) const {
    return (P.x >= 0 && P.x <= m_width && P.y >= 0 && P.y <= m_height && P.z >= 0 && P.z <= m_depth);
}