#include <monkey/math/shape.h>
#include <monkey/lua/luatable.h>

Shape::Shape(const LuaTable & t) : Object() {
    glm::vec2 offset = t.Get<glm::vec2>("offset", glm::vec2(0.0f));
    m_offset = glm::vec3(offset, 0.0f);
}