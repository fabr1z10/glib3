#include <monkey/math/shape.h>

Shape::Shape(const ITable & t) : Object() {
    glm::vec2 offset = t.get<glm::vec2>("offset", glm::vec2(0.0f));
    m_offset = glm::vec3(offset, 0.0f);
}
