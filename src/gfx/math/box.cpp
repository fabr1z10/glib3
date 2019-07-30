#include <gfx/math/box.h>
#include <gfx/error.h>
#include <gfx/visitor.h>

Box::Box(float width, float height, float depth, glm::vec3 offset) : Shape(offset), m_width(width), m_height(height), m_depth(depth) {
    m_bounds.min = offset;
    m_bounds.max = offset + glm::vec3(m_width, m_height, m_depth);
}

void Box::accept (AcyclicVisitor& v) {
    Visitor<Box>* v1 = dynamic_cast<Visitor<Box>*>(&v);
    if (v1 != 0)
        v1->visit(*this);
    else
        GLIB_FAIL("not a Box visitor");
}

bool Box::isPointInside(glm::vec3 P) const {
    return (P.x >= m_offset.x && P.x <= m_offset.x+m_width &&
            P.y >= m_offset.y && P.y <= m_offset.y+ m_height &&
            P.z >= m_offset.z && P.z <= m_offset.z+m_depth);
}