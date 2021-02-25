#include <monkey/math/shapes/rect.h>
#include <monkey/error.h>
#include <monkey/math/algo/geometry.h>

Rect::Rect(float width, float height, glm::vec3 offset) : IConvexPolygon(), m_width(width), m_height(height) {
    m_offset = offset;
    initBounds();
}

Rect::Rect(const ITable & t) : IConvexPolygon(t) {
    m_width = t.get<float>("width");
    m_height = t.get<float>("height");
    m_offset = t.get<glm::vec3> ("offset", glm::vec3(0.0f));
    initBounds();
}

//std::unique_ptr<IShape> Rect::transform(const glm::mat4 &t) {
//    auto ptr= std::make_unique<Rect>(m_width, m_height);
//    ptr->m_offset = t * glm::vec4(m_offset, 1.0f);
//    ptr->m_u = t * glm::vec4(m_u, 0.0f, 0.0f);
//    ptr->m_v = t * glm::vec4(m_v, 0.0f, 0.0f);
//    return ptr;
//}

void Rect::initBounds() {
    m_type = ShapeType::RECT;
    m_u = glm::vec2(1.0f, 0.0f);
    m_v = glm::vec2(0.0f, 1.0f);
    m_bounds.min = m_offset;
    m_bounds.max = m_offset + glm::vec3(m_width, m_height, 0.0f);
}

std::vector<glm::vec2> Rect::getEdges() const {
    return {m_u, m_v};
}

std::vector<glm::vec2> Rect::getVertices() const {
    glm::vec2 o(m_offset);
    glm::vec2 ax = m_u * m_width;
    glm::vec2 ay = m_v * m_height;
    return {o, o + ax, o + ax + ay, o + ay};
}


bool Rect::isPointInside(glm::vec3 P) const {

    // ignore z coord
    glm::vec2 l = P - m_offset;
    float uProj = glm::dot(l, m_u);
    if (uProj < 0 || uProj > m_width) {
        return false;
    }
    float vProj = glm::dot(l, m_v);
    return (vProj >= 0 && vProj < m_height);
}



//void Rect::accept (AcyclicVisitor& v) {
//    Visitor<Rect>* v1 = dynamic_cast<Visitor<Rect>*>(&v);
//    if (v1 != 0)
//        v1->visit(*this);
//    else
//        GLIB_FAIL("not a rect visitor");
//}
//
//
//std::string Rect::toString() const {
//    std::stringstream stream;
//    stream << "Rect (width = " << m_width << ", height = " << m_height << ")";
//    return stream.str();
//}

glm::vec2 Rect::project(glm::vec2 axis, const glm::mat4& t) const {
    glm::vec2 o(m_offset);
    glm::vec2 ax = m_u * m_width;
    glm::vec2 ay = m_v * m_height;
    std::vector<glm::vec2> points = {o, o + ax, o + ax + ay, o + ay};
    return ::project(points, axis, t);
}
//
//
//std::vector<glm::vec2> Rect::getPoints() {
//    return {
//            {m_offset.x, m_offset.y},
//            {m_offset.x, m_offset.y + m_height},
//            {m_offset.x + m_width, m_offset.y + m_height},
//            {m_offset.x + m_width, m_offset.y}
//    };
//}
//
//
//std::vector<glm::vec2> Rect::getEdges() {
//    return { glm::vec2(m_width, 0.0), glm::vec2(0.0, m_height)};
//}
