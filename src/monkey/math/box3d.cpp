#include <monkey/math/shapes/box3d.h>
#include <monkey/error.h>
#include <monkey/visitor.h>

Box3D::Box3D(float width, float height, float depth, glm::vec3 offset) : Shape(offset), m_width(width), m_height(height), m_depth(depth) {
    m_bounds.min = offset;
    m_bounds.max = offset + glm::vec3(m_width, m_height, m_depth);
}

void Box3D::accept (AcyclicVisitor& v) {
    Visitor<Box3D>* v1 = dynamic_cast<Visitor<Box3D>*>(&v);
    if (v1 != 0)
        v1->visit(*this);
    else
        GLIB_FAIL("not a Box3D visitor");
}

bool Box3D::isPointInside(glm::vec3 P) const {
    return (P.x >= m_offset.x && P.x <= m_offset.x+m_width &&
            P.y >= m_offset.y && P.y <= m_offset.y+ m_height &&
            P.z >= m_offset.z && P.z <= m_offset.z+m_depth);
}