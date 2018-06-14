#include <graph/shape.h>
#include <gfx/error.h>

bool Rect::isPointInside(glm::vec2 P) const {
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
