#include <monkey/math/shapes/convexpoly.h>
#include <monkey/math/algo/geometry.h>

ConvexPolygon::ConvexPolygon(const std::vector<glm::vec2>& pts) : m_points(pts) {
    init();
}

ConvexPolygon::ConvexPolygon(const ITable & t) {
    auto pts = t.get<std::vector<float>>("points");
    for (int i = 0; i < pts.size(); i += 2) {
        glm::vec2 cp(pts[i], pts[i+1]);
        m_points.push_back(cp);
    }
    init();
}

void ConvexPolygon::init() {
    for (unsigned i = 1; i < m_points.size(); ++i) {
        m_edges.push_back(glm::normalize(m_points[i] - m_points[i-1]));
    }
    m_edges.push_back(glm::normalize(m_points.front()-m_points.back()));

}

bool ConvexPolygon::isPointInside(glm::vec3 P) const {
    return pointInConvexPolygon(glm::vec2(P), m_points);
}

glm::vec2 ConvexPolygon::project(glm::vec2 axis) const {
    std::vector<glm::vec2> pts;
    for (const auto& p : m_points) pts.push_back(glm::vec2(m_offset) + p);
    return ::project(pts, axis);
}

std::unique_ptr<IShape> ConvexPolygon::transform(const glm::mat4 &t) {
    // transform each point
    std::vector<glm::vec2> points;
    for (const auto& p : m_points) {
        points.emplace_back(t * glm::vec4(p, 0.0f, 1.0f));
    }
    return std::make_unique<ConvexPolygon>(points);

}

