#include <gfx/math/plane3d.h>
#include <gfx/math/box.h>
#include <gfx/error.h>

// a plane3d always lies at y=0, you can only offset its x and z axes
Plane3D::Plane3D(float width, float depth, glm::vec2 offset) : Shape(glm::vec3(offset.x, 0, offset.y)), m_width(width), m_depth(depth) {
    glm::vec3 offset3d (offset.x, 0.0f, offset.y);
    m_bounds.min = offset3d;
    m_bounds.max = offset3d + glm::vec3(m_width, 0.0f, m_depth);

}


void Plane3D::accept (AcyclicVisitor& v) {
    Visitor<Plane3D>* v1 = dynamic_cast<Visitor<Plane3D>*>(&v);
    if (v1 != 0)
        v1->visit(*this);
    else
        GLIB_FAIL("not a Plane3D visitor");
}

bool Plane3D::isPointInside(glm::vec3 P) const {
    return (P.x >= m_bounds.min.x && P.x <= m_bounds.max.x && P.z >= m_bounds.min.z && P.z <= m_bounds.max.z);
}