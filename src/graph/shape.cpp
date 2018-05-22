#include <graph/shape.h>

bool Rect::isPointInside(glm::vec2 P) const {
    return !(P.x < 0 || P.x > m_width || P.y < 0 || P.y > m_height);
}