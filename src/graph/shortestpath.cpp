#include <graph/shortestpath.h>
#include <graph/graph.h>

void ShortestPath::visit(Polygon & p) {

    std::vector<glm::vec2> nodes;
    int n = p.GetVertexCount();
    for (int i=0; i<n; ++i) {
        if (p.isVertexConcave(i))
            nodes.push_back(p.GetVertex(i));
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



}