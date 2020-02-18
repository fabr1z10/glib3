#include <monkey/math/polyline.h>
#include <monkey/error.h>
#include <monkey/math/geom.h>
#include <monkey/lua/luatable.h>

PolyLine::PolyLine(const LuaTable & t) : Shape(t) {
    auto rVert = t.Get<luabridge::LuaRef>("vertices");
    for (int i = 0; i< rVert.length(); ++i) {
        luabridge::LuaRef vertex = rVert[i+1];
        glm::vec2 p(vertex[1].cast<float>(), vertex[2].cast<float>());
        m_vertices.push_back(p);
    }
    auto rEdges = t.Get<luabridge::LuaRef>("edges");
    for (int i = 0; i< rEdges.length(); ++i) {
        luabridge::LuaRef edge = rEdges[i+1];
        std::pair<int, int> e(edge[1].cast<int>(), edge[2].cast<int>());
        m_edgeIndices.push_back(e);
    }
    for (auto& e : m_edgeIndices) {
        m_edges.emplace_back(std::make_pair(m_vertices[e.first], m_vertices[e.second]));
    }


}

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

bool PolyLine::isPointInside (glm::vec3 P) const {
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
