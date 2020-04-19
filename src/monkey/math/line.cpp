#include <monkey/math/line.h>
#include <monkey/math/geom.h>
#include <monkey/math/geomalgo.h>
#include <monkey/error.h>
#include <vector>


Line::Line(const ITable& t) : Shape() {
    m_A = t.get<glm::vec3>("A");
    m_B = t.get<glm::vec3>("B");
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
    m_bounds.min.z = -1.0f;
    m_bounds.max.z = 1.0f;
    m_length = glm::length(m_B - m_A);
    m_length = glm::dot(m_B - m_A, m_B - m_A);
    m_dir = glm::normalize(m_B - m_A);
}
Line::Line (glm::vec2 A, glm::vec2 B) : Shape(), m_A(A, 0.0f), m_B(B, 0.0f) {
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
    m_bounds.min.z = -1.0f;
    m_bounds.max.z = 1.0f;
    m_length = glm::length(m_B - m_A);
    m_length = glm::dot(m_B - m_A, m_B - m_A);
    m_dir = glm::normalize(m_B - m_A);

}
Line::Line (glm::vec3 A, glm::vec3 B) : Shape(), m_A{A}, m_B{B} {
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
    if (m_A.z < m_B.z) {
        m_bounds.min.z = m_A.z;
        m_bounds.max.z = m_B.z;
    } else {
        m_bounds.min.z = m_B.z;
        m_bounds.max.z = m_A.z;
    }
    m_length = glm::length(m_B - m_A);
    m_length = glm::dot(m_B - m_A, m_B - m_A);
    m_dir = glm::normalize(m_B - m_A);

}

bool Line::isPointInside(glm::vec3 P) const {
//    glm::vec3 a = P - m_A;
//    glm::vec3 b = m_B - m_A;
//    float c = cross(a, b);
//    if (fabs(c) > epsilon)
//        return false;
//    float d = glm::dot(a, b);
//    if (d < 0)
//        return false;
//    if (d > m_length2)
//        return false;
//    return true;
    return false;
}

void Line::accept (AcyclicVisitor& v) {
    Visitor<Line>* v1 = dynamic_cast<Visitor<Line>*>(&v);
    if (v1 != 0)
        v1->visit(*this);
    else
        GLIB_FAIL("not a line visitor");
}


std::string Line::toString() const {
    std::stringstream stream;
    stream << "Line (A = (" << m_A.x << ", " << m_A.y << "), height = (" << m_B.x << ", " << m_B.y << "))";
    return stream.str();
}

glm::vec2 Line::project(const glm::vec2 axis, const glm::mat4& worldTransform) {
    std::vector<glm::vec2> points = {
        m_A, m_B
    };
    return Projection(points, axis, worldTransform);
}


std::vector<glm::vec2> Line::getPoints() {
    // for a segment the point
    return { m_A, m_B};
}

std::vector<glm::vec2> Line::getEdges() {
    return {m_B - m_A};
}
