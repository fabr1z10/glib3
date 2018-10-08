#include <gfx/math/shortestpath.h>
#include <gfx/math/graph.h>
#include <gfx/math/algo.h>

void ShortestPath::visit(PolyLine& p) {


    int es = p.GetEdgeContaining(m_A);
    int ee = p.GetEdgeContaining(m_B);

    // start and end points lie on the same edge. Nothing to do here!
    if (es == ee) {
        m_result.push_back(m_A);
        m_result.push_back(m_B);
        return;
    }

    Graph<int, glm::vec2> g;

    // get all vertices
    const auto& vertices = p.GetVertices();
    const auto& edgeIndices = p.GetEdgeIndices();
    int count = 0;
    for (auto& v : vertices) {
        g.AddNode(count++, v);
    }
    for (auto& e : edgeIndices) {
        float w = glm::distance(vertices[e.first], vertices[e.second]);
        g.AddEdge(e.first, e.second, w);
    }
    // add start and end points to the graph
    int iStart = count;
    int iEnd = count+1;
    g.AddNode(iStart, m_A);
    g.AddNode(iEnd, m_B);
    // add connections
    g.AddEdge(iStart, edgeIndices[es].first, glm::distance(m_A, vertices[edgeIndices[es].first]));
    g.AddEdge(iStart, edgeIndices[es].second, glm::distance(m_A, vertices[edgeIndices[es].second]));
    g.AddEdge(iEnd, edgeIndices[ee].first, glm::distance(m_A, vertices[edgeIndices[ee].first]));
    g.AddEdge(iEnd, edgeIndices[ee].second, glm::distance(m_A, vertices[edgeIndices[ee].second]));


    // now you need to add to the graph the start and end point
    // plus you need to find the index of the edges containing the start, and end point
    // let e_s and e_e the edge containing start and edge containing end.
    // now you need to draw edges from start to the vertices of e_s and edges from e to the vertices of e_e
    // if e_s = e_e also
    auto res = FindShortestPath(g, iStart, iEnd);
    for (auto& p : res) m_result.push_back(g.GetValue(p));


}


void ShortestPath::visit(Polygon & p) {

    std::vector<glm::vec2> nodes;
    int n = p.GetVertexCount();
    for (int i=0; i<n; ++i) {
        if (p.isVertexConcave(i)) {
            glm::vec2 n = p.getNormalAtVertex(i);
            nodes.push_back(p.GetVertex(i) - n*0.01f);
        }
    }
    // now add start and end points
    if (nodes.empty()) {
        // no concave nodes, so polygon is convex. Therefore...
        m_result.push_back(m_A);
        m_result.push_back(m_B);
        return;
    }

    nodes.push_back(m_A);
    nodes.push_back(m_B);
    // create the graph
    Graph<int, glm::vec2> g;
    int i = 0;
    for (auto& p : nodes)
        g.AddNode(i++, p);
    // add edge (i, j) only if ij are in line of sight
    for (int i = 0; i < nodes.size(); ++i) {
        for (int j = i+1; j < nodes.size(); ++j) {
            if (p.isInLineOfSight(nodes[i], nodes[j]))
                g.AddEdge(i, j, glm::distance(nodes[i], nodes[j]));
        }
    }
    int keyFrom = nodes.size() -2;
    int keyTo = nodes.size() - 1;
    auto res = FindShortestPath(g, keyFrom, keyTo);
    for (auto& p : res) m_result.push_back(g.GetValue(p));


}

void ShortestPath::visit(Poly& p) {

    std::vector<glm::vec2> nodes;
    Polygon* pMain = p.GetPolygon(0);
    int n = pMain->GetVertexCount();
    for (int i=0; i<n; ++i) {
        if (pMain->isVertexConcave(i)) {
            glm::vec2 n = pMain->getNormalAtVertex(i);
            nodes.push_back(pMain->GetVertex(i) - n*0.01f);
        }
    }

    // add convex point of holes
    int nHoles = p.GetHoleCount();
    for (int i = 0; i<nHoles; ++i) {
        Polygon* pHole = p.GetPolygon(i+1);
        int n = pHole->GetVertexCount();
        for (int j=0; j<n; ++j) {
            if (pHole->isVertexConcave(j)) {
                glm::vec2 n = pHole->getNormalAtVertex(j);
                nodes.push_back(pHole->GetVertex(j) - n*0.01f);
            }
        }
    }


    // now add start and end points
    if (nodes.empty()) {
        // no concave nodes, so polygon is convex. Therefore...
        m_result.push_back(m_A);
        m_result.push_back(m_B);
        return;
    }

    nodes.push_back(m_A);
    nodes.push_back(m_B);
    // create the graph
    Graph<int, glm::vec2> g;
    int i = 0;
    for (auto& p : nodes)
        g.AddNode(i++, p);
    // add edge (i, j) only if ij are in line of sight
    for (int i = 0; i < nodes.size(); ++i) {
        for (int j = i+1; j < nodes.size(); ++j) {
            if (p.isInLineOfSight(nodes[i], nodes[j]))
                g.AddEdge(i, j, glm::distance(nodes[i], nodes[j]));
        }
    }
    int keyFrom = nodes.size() -2;
    int keyTo = nodes.size() - 1;
    auto res = FindShortestPath(g, keyFrom, keyTo);
    for (auto& p : res) m_result.push_back(g.GetValue(p));


}

std::vector<glm::vec2> ShortestPath::Find(Shape& s, glm::vec2 A, glm::vec2 B) {
    ShortestPath sp(A, B);
    s.accept(sp);
    return sp.m_result;
}


