#include <monkey/math/triangle.h>
#include <monkey/math/geomalgo.h>

Triangle::Triangle (const glm::vec2& A, const glm::vec2& B, const glm::vec2& C) : Shape()
{
    m_points.push_back(A);
    m_points.push_back(B);
    m_points.push_back(C);
    computeBounds();

}

void Triangle::computeBounds() {
    m_edges.push_back(m_points[1]-m_points[0]);
    m_edges.push_back(m_points[2]-m_points[1]);
    m_edges.push_back(m_points[0]-m_points[2]);

    m_bounds.min = glm::vec3(m_points[0].x, m_points[0].y, 0.0f);
    m_bounds.max = glm::vec3(m_points[0].x, m_points[0].y, 0.0f);
    for (int i =1; i<3; ++i) {
        m_bounds.min.x = std::min(m_bounds.min.x, m_points[i].x);
        m_bounds.min.y = std::min(m_bounds.min.y, m_points[i].y);
        m_bounds.max.x = std::max(m_bounds.max.x, m_points[i].x);
        m_bounds.max.y = std::max(m_bounds.max.y, m_points[i].y);
    }

}
Triangle::Triangle (const ITable& t) : Shape(t) {
    m_points.push_back(t.get<glm::vec2>("A"));
    m_points.push_back(t.get<glm::vec2>("B"));
    m_points.push_back(t.get<glm::vec2>("C"));


    computeBounds();
}

bool Triangle::isPointInside(glm::vec3 p) const {
    glm::vec2 P(p.x, p.y);
    return PointInTriangle(P, m_points[0], m_points[1], m_points[2]);
}


void Triangle::accept (AcyclicVisitor& v) {
    Visitor<Triangle>* v1 = dynamic_cast<Visitor<Triangle>*>(&v);
    if (v1 != 0)
        v1->visit(*this);
    else
        GLIB_FAIL("not a triangle visitor");
}

std::vector<glm::vec2> Triangle::getEdges() {
    return m_edges;
}

std::vector<glm::vec2> Triangle::getPoints() {
    return {m_points[0], m_points[1], m_points[2]};
}

glm::vec2 Triangle::project(const glm::vec2 axis, const glm::mat4& worldTransform) {
    return Projection(m_points, axis, worldTransform);
}

std::string Triangle::toString() const {
    return "";
}
