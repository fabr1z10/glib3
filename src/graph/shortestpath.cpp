#include <graph/shortestpath.h>
#include <graph/graph.h>
#include <graph/algo.h>


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
