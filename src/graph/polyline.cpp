#include <graph/polyline.h>
#include <gfx/error.h>
#include <graph/geom.h>

PolyLine::PolyLine (const std::vector<glm::vec2>& vertices, const std::vector<std::pair<int, int>>& edges) {
    m_vertices = vertices;
    m_edgeIndices = edges;
    for (auto& e : edges)
        m_edges.push_back(std::make_pair(vertices[e.first], vertices[e.second]));
}

void PolyLine::accept (AcyclicVisitor& v) {
    Visitor<PolyLine>* v1 = dynamic_cast<Visitor<PolyLine>*>(&v);
    if (v1 != 0)
        v1->visit(*this);
    else
        GLIB_FAIL("not a polyline visitor");
}

bool PolyLine::isPointInside (glm::vec2 P) const {
    return false;
}

int PolyLine::GetEdgeContaining(glm::vec2 P) {
    for (int i = 0; i < m_edges.size(); ++i) {
        if (IsBetween(m_edges[i].first, m_edges[i].second, P))
            return i;
    }
    return -1;
}

std::string PolyLine::toString() const {
    return "Polyline";
}
