#include <monkey/math/shapes/polyline.h>
//#include <monkey/error.h>
//#include <monkey/math/geom.h>
//

namespace py = pybind11;


PolyLine::PolyLine(const ITab & t) : IShape(t) {
    m_type = ShapeType::POLYLINE;
    auto rvert = t.get<std::vector<float>>("nodes");
    for (size_t i = 0; i < rvert.size(); i += 2) {
        m_vertices.emplace_back(rvert[i], rvert[i+1]);
    }
    auto redges = t.get<std::vector<int>>("edges");
    for (size_t i = 0; i < redges.size(); i+= 2) {
        m_edgeIndices.emplace_back(redges[i], redges[i+1]);
    }

    for (auto& e : m_edgeIndices) {
        m_edges.emplace_back(std::make_pair(m_vertices[e[0]], m_vertices[e[1]]));
    }
}
//    auto rVert = t.get<py::list>("nodes");
//    for (const auto& l : rVert) {
//        auto v = l.cast<std::vector<float>>();
//        glm::vec2 p (v[0], v[1]);
//        m_vertices.push_back(p);
//    }
//    auto rEdges = t.get<py::list>("edges");
//    for (const auto& edge : rEdges) {
//        auto v = edge.cast<std::vector<int>>();
//        std::pair<int, int> e(v[0], v[1]);
//        m_edgeIndices.push_back(e);
//    }
//    for (auto& e : m_edgeIndices) {
//        m_edges.emplace_back(std::make_pair(m_vertices[e.first], m_vertices[e.second]));
//    }
//
//
//}
//
//
//PolyLine::PolyLine (const std::vector<glm::vec2>& vertices, const std::vector<std::pair<int, int>>& edges) {
//    m_vertices = vertices;
//    m_edgeIndices = edges;
//    for (auto& e : edges)
//        m_edges.push_back(std::make_pair(vertices[e.first], vertices[e.second]));
//}
//
//void PolyLine::accept (AcyclicVisitor& v) {
//    Visitor<PolyLine>* v1 = dynamic_cast<Visitor<PolyLine>*>(&v);
//    if (v1 != 0)
//        v1->visit(*this);
//    else
//        GLIB_FAIL("not a polyline visitor");
//}
//
bool PolyLine::isPointInside (glm::vec3 P) const {
    return false;
}
//
//int PolyLine::GetEdgeContaining(glm::vec2 P) {
//    for (int i = 0; i < m_edges.size(); ++i) {
//        if (IsBetween(m_edges[i].first, m_edges[i].second, P))
//            return i;
//    }
//    return -1;
//}
//
//std::string PolyLine::toString() const {
//    return "Polyline";
//}
