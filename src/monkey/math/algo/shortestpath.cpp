#include <monkey/math/algo/shortestpath.h>
#include <monkey/math/shapes/poly.h>



//#include <monkey/math/graph.h>
//#include <monkey/math/algo.h>
//




//bool ShortestPath::pointInPoly(glm::vec2 P) {
//    // One simple way of finding whether the point is inside or outside a simple polygon is to test how many times a ray,
//    // starting from the point and going in any fixed direction, intersects the edges of the polygon. If the point is on
//    // the outside of the polygon the ray will intersect its edge an even number of times. If the point is on the inside
//    // of the polygon then it will intersect the edge an odd number of times. The status of a point on the edge of the
//    // polygon depends on the details of the ray intersection algorithm.
//    const auto& vertices = m_shape->getOutlineVertices();
//    glm::vec2 Q = P + glm::vec2(1.0f, 0.0f);
//    float t = 0.0f, u = 0.0f;
//    bool contained = false;
//    for (int i = 0; i < vertices.size(); i++) {
//        glm::vec2 a = vertices[i];
//        glm::vec2 b = vertices[(i+1)%vertices.size()];
//        // if point is contained
//        auto r = linint(P, Q, a, b, t, u);
//        // don't consider parallel/collinear
//        if (r == 2) {
//        	if ((P.x >= a.x && P.x <= b.x) || (P.x >= b.x && P.x <= a.x)) {
//        		return true;
//        	}
//        }
//		if (r == 0) {
//			if (fabs(t) < m_eps) {
//				// point is contained in segment
//				return true;
//			}
//			// if ray intersects segment flip the contained flag
//			if (t > 0 && u >= 0 && u <= 1.0f) {
//				contained = !contained;
//			}
//		}
//    }
//    return contained;
//
//}





void IShortestPath::addWall(glm::vec2 A, glm::vec2 B, bool active) {
    m_walls.push_back(Wall{A, B, active});
}


void IShortestPath::setWall(int id, bool active) {
    m_walls[id].active = active;
    updateGraph();
}

//void ShortestPath::updateGraph(PolyLine * pline) {
//    m_graph = std::make_shared<Graph<int, glm::vec2>>();
//    m_graphNoWalls = std::make_shared<Graph<int, glm::vec2>>();
//    const auto& vertices = pline->getVertices();
//    for (size_t i = 0; i < vertices.size(); ++i) {
//        m_graph->addNode(i, vertices[i]);
//        m_graphNoWalls->addNode(i, vertices[i]);
//    }
//    for (const auto& e : pline->getEdges()) {
//        m_graph->addEdge(e.x, e.y, glm::length(vertices[e.x] - vertices[e.y]));
//        m_graphNoWalls->addEdge(e.x, e.y, glm::length(vertices[e.x] - vertices[e.y]));
//    }
//}





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

const std::vector<Wall> & IShortestPath::getWalls() const {
    return m_walls;
}