#include <monkey/math/shape.h>


IShape::IShape(const ITable & t) : Object() {
    m_offset = t.get<glm::vec3>("offset", glm::vec3(0.0f));
}
