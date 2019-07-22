#include <gfx/math/plane3d.h>
#include <gfx/math/box.h>
#include <gfx/error.h>

Plane3D::Plane3D(float width, float depth) : Shape(), m_width(width), m_depth(depth) {

    m_bounds.min = glm::vec3(0.0f, 0.0f, 0.f);
    m_bounds.max = glm::vec3(m_width, 0.0f, m_depth);

}


void Plane3D::accept (AcyclicVisitor& v) {
    Visitor<Plane3D>* v1 = dynamic_cast<Visitor<Plane3D>*>(&v);
    if (v1 != 0)
        v1->visit(*this);
    else
        GLIB_FAIL("not a Plane3D visitor");
}

bool Plane3D::isPointInside(glm::vec3 P) const {
    return (P.x >= 0 && P.x <= m_width && P.z >= 0 && P.z <= m_depth);
}