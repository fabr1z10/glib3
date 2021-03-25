#include <monkey/math/algo/shortestpath.h>
#include <monkey/math/shapes/poly.h>
#include <monkey/math/geom.h>
#include <monkey/math/algo/geometry.h>
//#include <monkey/math/graph.h>
//#include <monkey/math/algo.h>
//

ShortestPath::ShortestPath() {}



void ShortestPath::addNode(Polygon* p, glm::vec2 point) {
    // adds a node to the graph
    // and an edge from the new node to every other node that is in line of sight with it
    int id = m_graph->getVertexCount();

    m_graph->addNode(id, point);
    // add one edge to other nodes if they are in LOS
    for (const auto& node : m_graph->getNodes()) {
        if (node.first != id) {
            glm::vec2 P = node.second;
            // checks to see if there's any intersection with the edges
            // you need to check outline and active holes
            const auto& vertices = p->getOutlineVertices();
            bool intersection = false;
            for (int i = 0; i < vertices.size(); i++) {
                glm::vec2 a = vertices[i];
                glm::vec2 b = vertices[(i+1)%vertices.size()];
                std::cerr << " seg intersect: (" << point.x << ", " << point.y << ") - (" << P.x << ", " << P.y << "), (" <<
                a.x << ", " << a.y << ") - (" << b.x << ", " <<
                b.y << ") ...";
                // if one of the two points match, within a certain tolerance, no intersection
                bool m = match(point, a, 0.01f) || match(point, b, 0.01f) || match(P, a, 0.01f) || match(P, b, 0.01f);
                if (!m && segmentIntersection(point, P, a, b)) {
                    // if we have intersection, no edge is needed
                    std::cerr << " YES\n";
                    intersection = true;
                    break;
                } else {
                    std::cerr << " NO\n";
                }
            }
            for (int i = 0; !intersection && i < p->getHoleCount(); ++i) {
                if (m_inactiveHoles.count(i) == 0) {
                    const auto& vertices = p->getHoleVertices(i);
                    for (int i = 0; i < vertices.size(); i++) {
                        if (segmentIntersection(point, P, vertices[i], vertices[i+1 % vertices.size()])) {
                            intersection = true;
                            break;
                        }
                    }
                }
            }

            if (!intersection) {
                // check mid point. The segment might connect two vertices of the polygon but lie completely outside of it
                // quick way is to check if mid point of the segment lies inside the poly
                auto midPoint = 0.5f * (point + P);
                if (p->isPointInside(glm::vec3(midPoint, 0.0f))) {
                    // add edge
                    m_graph->addEdge(id, node.first, glm::length(point - P));
                }


            }

        }
    }

}

void ShortestPath::addPoly(Polygon* p, const std::vector<glm::vec2> & outline, float flip) {

    size_t n = outline.size();
    for (size_t i = 0; i < n; ++i) {
        size_t inext = (i + 1) % n;
        size_t iprev = (i == 0) ? n - 1 : i - 1;
        glm::vec2 v0 = outline[i] - outline[iprev];
        glm::vec2 v1 = outline[inext] - outline[i];
        auto f = cross(v0, v1) * flip;
        // assume outline is specified counterclockwise
        // therefore a concave vertex
        int id = m_graph->getVertexCount();
        if (f < 0) {
            addNode(p, outline[i]);
        }


    }
}

void ShortestPath::setShape(std::shared_ptr<IShape> shape) {
    m_shape = shape;
    m_graph = std::make_shared<Graph<int, glm::vec2>>();
    auto type = m_shape->getShapeType();
    if (type == ShapeType::POLY) {
        auto poly = std::static_pointer_cast<Polygon>(shape);
        // get edges to test for LOS
        std::vector<glm::vec2> edges;
        auto outline = poly->getOutlineVertices();
        addPoly(poly.get(), outline);
        for (int i = 0; i < poly->getHoleCount(); ++i) {
            if (m_inactiveHoles.count(i) == 0) {
                addPoly(poly.get(), poly->getHoleVertices(i), -1.0f);
            }
        }

    }
    std::cout << "nodes\n-----\n";
    for (const auto& node : m_graph->getNodes()) {
        std::cout << node.first << ": " << node.second.x << ", " << node.second.y << "\n";
    }
    std::cout << "edges\n-----\n";
    for (const auto& e : m_graph->getEdges()) {
        for (const auto& edge : e.second) {
            std::cout << e.first << " --> " << edge.first << " (" << edge.second << ")\n";
        }
    }
    exit(1);
}



//void ShortestPath::visit(PolyLine& p) {
//
//
//    int es = p.GetEdgeContaining(m_A);
//    int ee = p.GetEdgeContaining(m_B);
//
//    // start and end points lie on the same edge. Nothing to do here!
//    if (es == ee) {
//        m_result.push_back(m_A);
//        m_result.push_back(m_B);
//        return;
//    }
//
//    Graph<int, glm::vec2> g;
//
//    // get all vertices
//    const auto& vertices = p.GetVertices();
//    const auto& edgeIndices = p.GetEdgeIndices();
//    int count = 0;
//    for (auto& v : vertices) {
//        g.AddNode(count++, v);
//    }
//    for (auto& e : edgeIndices) {
//        float w = glm::distance(vertices[e.first], vertices[e.second]);
//        g.AddEdge(e.first, e.second, w);
//    }
//    // add start and end points to the graph
//    int iStart = count;
//    int iEnd = count+1;
//    g.AddNode(iStart, m_A);
//    g.AddNode(iEnd, m_B);
//    // add connections
//    g.AddEdge(iStart, edgeIndices[es].first, glm::distance(m_A, vertices[edgeIndices[es].first]));
//    g.AddEdge(iStart, edgeIndices[es].second, glm::distance(m_A, vertices[edgeIndices[es].second]));
//    g.AddEdge(iEnd, edgeIndices[ee].first, glm::distance(m_A, vertices[edgeIndices[ee].first]));
//    g.AddEdge(iEnd, edgeIndices[ee].second, glm::distance(m_A, vertices[edgeIndices[ee].second]));
//
//
//    // now you need to add to the graph the start and end point
//    // plus you need to find the index of the edges containing the start, and end point
//    // let e_s and e_e the edge containing start and edge containing end.
//    // now you need to draw edges from start to the vertices of e_s and edges from e to the vertices of e_e
//    // if e_s = e_e also
//    auto res = FindShortestPath(g, iStart, iEnd);
//    for (auto& p : res) m_result.push_back(g.GetValue(p));
//
//
//}
//
//
//void ShortestPath::visit(Polygon & p) {
//
//    std::vector<glm::vec2> nodes;
//    int n = p.GetVertexCount();
//    for (int i=0; i<n; ++i) {
//        if (p.isVertexConcave(i)) {
//            glm::vec2 n = p.getNormalAtVertex(i);
//            nodes.push_back(p.GetVertex(i) - n*0.01f);
//        }
//    }
//    // now add start and end points
//    if (nodes.empty()) {
//        // no concave nodes, so polygon is convex. Therefore...
//        m_result.push_back(m_A);
//        m_result.push_back(m_B);
//        return;
//    }
//
//    nodes.push_back(m_A);
//    nodes.push_back(m_B);
//    // create the graph
//    Graph<int, glm::vec2> g;
//    int i = 0;
//    for (auto& p : nodes)
//        g.AddNode(i++, p);
//    // add edge (i, j) only if ij are in line of sight
//    for (int i = 0; i < nodes.size(); ++i) {
//        for (int j = i+1; j < nodes.size(); ++j) {
//            if (p.isInLineOfSight(nodes[i], nodes[j]))
//                g.AddEdge(i, j, glm::distance(nodes[i], nodes[j]));
//        }
//    }
//    int keyFrom = nodes.size() -2;
//    int keyTo = nodes.size() - 1;
//    auto res = FindShortestPath(g, keyFrom, keyTo);
//    for (auto& p : res) m_result.push_back(g.GetValue(p));
//
//
//}
//
//void ShortestPath::visit(Poly& p) {
//
//    std::vector<glm::vec2> nodes;
//    Polygon* pMain = p.GetPolygon();
//    int n = pMain->GetVertexCount();
//    for (int i=0; i<n; ++i) {
//        if (pMain->isVertexConcave(i)) {
//            glm::vec2 n = pMain->getNormalAtVertex(i);
//            nodes.push_back(pMain->GetVertex(i)-  n*0.01f);
//        }
//    }
//
//    // add convex point of holes
//    const auto& holes = p.getHoles();
//    for (const auto& hole : holes) {
//        glm::vec2 holePos(hole.getPosition());
//        int n = hole.getVertexCount();
//        for (int j = 0; j < n; ++j) {
//            if (!hole.isVertexConcave(j)) {
//                glm::vec2 n = hole.getNormalAtVertex(j);
//                glm::vec2 vertex = hole.getVertex(j);
//
//                nodes.push_back(hole.getVertex(j) + holePos + n * 0.01f);
//            }
//
//        }
//
//    }
//
//
//    // now add start and end points
//    if (nodes.empty()) {
//        // no concave nodes, so polygon is convex. Therefore...
//        m_result.push_back(m_A);
//        m_result.push_back(m_B);
//        return;
//    }
//
//    nodes.push_back(m_A);
//    nodes.push_back(m_B);
//    // create the graph
//    Graph<int, glm::vec2> g;
//    int i = 0;
//    for (auto& p : nodes)
//        g.AddNode(i++, p);
//    // add edge (i, j) only if ij are in line of sight
//    for (int i = 0; i < nodes.size(); ++i) {
//        for (int j = i+1; j < nodes.size(); ++j) {
//            if (p.isInLineOfSight(nodes[i], nodes[j]))
//                g.AddEdge(i, j, glm::distance(nodes[i], nodes[j]));
//        }
//    }
//    int keyFrom = nodes.size() -2;
//    int keyTo = nodes.size() - 1;
//    auto res = FindShortestPath(g, keyFrom, keyTo);
//    for (auto& p : res) m_result.push_back(g.GetValue(p));
//
//
//}
//
//std::vector<glm::vec2> ShortestPath::Find(Shape& s, glm::vec2 A, glm::vec2 B) {
//    ShortestPath sp(A, B);
//    s.accept(sp);
//    return sp.m_result;
//}
//
//
