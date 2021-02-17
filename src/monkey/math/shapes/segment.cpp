#include <monkey/math/shapes/line.h>
#include <monkey/math/geom.h>
#include <monkey/math/geomalgo.h>
#include <monkey/error.h>
#include <vector>


Segment::Segment(const ITable& t) : IConvexPolygon(t) {
    m_A = t.get<glm::vec2>("A");
    m_B = t.get<glm::vec2>("B");
    initBounds();


}

Segment::Segment (glm::vec2 A, glm::vec2 B) : IConvexPolygon(), m_A(A), m_B(B) {
    initBounds();
}


std::unique_ptr<IShape> Segment::transform(const glm::mat4 &t) {
    glm::vec3 ta = t * glm::vec4(m_A, 0.0f, 1.0f);
    glm::vec3 tb = t * glm::vec4(m_B, 0.0f, 1.0f);
    auto ptr= std::make_unique<Segment>(ta, tb);
    return ptr;
}

void Segment::initBounds() {
    m_type = ShapeType::SEGMENT;

    m_dir = glm::normalize(m_B - m_A);
    if (m_A.x < m_B.x) {
        m_bounds.min.x = m_A.x;
        m_bounds.max.x = m_B.x;
    } else {
        m_bounds.min.x = m_B.x;
        m_bounds.max.x = m_A.x;
    }

    if (m_A.y < m_B.y) {
        m_bounds.min.y = m_A.y;
        m_bounds.max.y = m_B.y;
    } else {
        m_bounds.min.y = m_B.y;
        m_bounds.max.y = m_A.y;
    }

}


glm::vec2 Segment::getDirection() const {
    return m_dir;
}

float Segment::getLength() const {
    return glm::length(m_B - m_A);
}

glm::vec2 Segment::project(glm::vec2 axis) const {
    float a = glm::dot(m_A, axis);
    float b = glm::dot(m_B, axis);
    if (a < b) {
        return glm::vec2(a, b);
    }
    return glm::vec2(b, a);
}

bool Segment::isPointInside(glm::vec3 P) const {
    glm::vec2 p(P);
    glm::vec3 a(p-m_A, 0.0f);
    glm::vec3 b(m_B-m_A, 0.0f);
    if (isZero(glm::cross(a, b).z)) {
        // collinear
        if (m_A.x != m_B.x) {
            return m_A.x <= P.x && P.x <= m_B.x;
        } else {
            return m_A.y <= P.y && P.y <= m_B.y;
        }
    }
    return false;
}

std::vector<glm::vec2> Segment::getEdges() const {
    return {m_dir};
}

std::vector<glm::vec2> Segment::getVertices() const {
    return {m_A, m_B};
}