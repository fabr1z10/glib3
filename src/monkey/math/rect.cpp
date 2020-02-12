#include <monkey/math/rect.h>
#include <monkey/error.h>
#include <monkey/math/geomalgo.h>
#include <monkey/lua/luatable.h>

Rect::Rect(const LuaTable & t) : Shape(t) {
    m_width = t.Get<float>("width");
    m_height = t.Get<float>("height");
    initBounds();
}

void Rect::initBounds() {
    m_bounds.min = m_offset;
    m_bounds.max = m_offset + glm::vec3(m_width, m_height, 0.0f);
    m_bounds.min.z -= 1.0f;
    m_bounds.max.z += 1.0f;
}

bool Rect::isPointInside(glm::vec3 P) const {
    // ignore z coord
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


std::string Rect::toString() const {
    std::stringstream stream;
    stream << "Rect (width = " << m_width << ", height = " << m_height << ")";
    return stream.str();
}

glm::vec2 Rect::project(const glm::vec2 axis, const glm::mat4& worldTransform) {
    std::vector<glm::vec2> points = {
            {m_offset.x, m_offset.y},
            {m_offset.x+m_width, m_offset.y},
            {m_offset.x, m_offset.y + m_height},
            {m_offset.x+m_width, m_offset.y+m_height}
    };
    return Projection(points, axis, worldTransform);
}


std::vector<glm::vec2> Rect::getPoints() {
    return {
            {m_offset.x, m_offset.y},
            {m_offset.x, m_offset.y + m_height},
            {m_offset.x + m_width, m_offset.y + m_height},
            {m_offset.x + m_width, m_offset.y}
    };
}


std::vector<glm::vec2> Rect::getEdges() {
    return { glm::vec2(m_width, 0.0), glm::vec2(0.0, m_height)};
}
