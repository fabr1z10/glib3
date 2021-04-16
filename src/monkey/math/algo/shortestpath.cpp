#include <monkey/math/algo/shortestpath.h>
#include <monkey/math/shapes/poly.h>
#include <monkey/math/geom.h>
#include <monkey/math/algo/geometry.h>
#include <monkey/math/algo/closest.h>
#include <glm/gtx/vector_angle.hpp>
//#include <monkey/math/graph.h>
//#include <monkey/math/algo.h>
//

ShortestPath::ShortestPath() : m_eps(0.01f) {}


bool ShortestPath::pointInPoly(glm::vec2 P) {
    // One simple way of finding whether the point is inside or outside a simple polygon is to test how many times a ray,
    // starting from the point and going in any fixed direction, intersects the edges of the polygon. If the point is on
    // the outside of the polygon the ray will intersect its edge an even number of times. If the point is on the inside
    // of the polygon then it will intersect the edge an odd number of times. The status of a point on the edge of the
    // polygon depends on the details of the ray intersection algorithm.
    const auto& vertices = m_shape->getOutlineVertices();
    glm::vec2 Q = P + glm::vec2(1.0f, 0.0f);
    float t = 0.0f, u = 0.0f;
    bool contained = false;
    for (int i = 0; i < vertices.size(); i++) {
        glm::vec2 a = vertices[i];
        glm::vec2 b = vertices[(i+1)%vertices.size()];
        // if point is contained
        auto r = linint(P, Q, a, b, t, u);
        // don't consider parallel/collinear
        if (r == 2) {
        	if ((P.x >= a.x && P.x <= b.x) || (P.x >= b.x && P.x <= a.x)) {
        		return true;
        	}
        }
		if (r == 0) {
			if (fabs(t) < m_eps) {
				// point is contained in segment
				return true;
			}
			// if ray intersects segment flip the contained flag
			if (t > 0 && u >= 0 && u <= 1.0f) {
				contained = !contained;
			}
		}
    }
    return contained;

}


void ShortestPath::removeNode(int id) {
    m_graph->removeNode(id);
    m_graphNoWalls->removeNode(id);
}

int ShortestPath::addNode(glm::vec2 point) {
    // adds a node to the graph
    // and an edge from the new node to every other node that is in line of sight with it
    int id = m_graph->getVertexCount();
    m_graph->addNode(id, point);
    m_graphNoWalls->addNode(id, point);
    // add one edge to other nodes if they are in LOS

    for (const auto& node : m_graph->getNodes()) {
        if (node.first != id) {
            glm::vec2 P = node.second;
            // checks to see if there's any intersection with the edges
            // you need to check all edges
            bool intersection = false;
            bool intersectWithWall = false;
            for (const auto& edge : m_edges) {
                float t = 0, u = 0;
                if (segmentIntersection(point, P, edge.A, edge.B, t, u)) {
                    float len = glm::length(point - P);
                    float dist = t * len;
                    if ( (dist > m_eps && dist < len - m_eps) ) { //|| ( u > m_eps && u < 1.0f - m_eps)) {
                        if (edge.wallEdge) {
                            intersectWithWall = true;
                        } else {
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
                if (this->pointInPoly(midPoint)) {
                    // add edge
                    m_graphNoWalls->addEdge(id, node.first, glm::length(point - P));
                    if (!intersectWithWall) {
                        m_graph->addEdge(id, node.first, glm::length(point - P));
                    }
                }


            }

        }
    }
    return id;
}

void ShortestPath::addPoly(const std::vector<glm::vec2> & outline, float flip) {

    size_t n = outline.size();
    for (size_t i = 0; i < n; ++i) {
        size_t inext = (i + 1) % n;
        size_t iprev = (i == 0) ? n - 1 : i - 1;
        glm::vec2 v0 = outline[i] - outline[iprev];
        glm::vec2 v1 = outline[inext] - outline[i];
        auto f = cross(v0, v1) * flip;
        // assume outline is specified counterclockwise
        // therefore a concave vertex
        if (f < 0) {
            addNode(outline[i]);
        }


    }
}

void ShortestPath::addWall(glm::vec2 A, glm::vec2 B, bool active) {
    m_walls.push_back(Wall{A, B, active});
}


void ShortestPath::setWall(int id, bool active) {
    m_walls[id].active = active;
}

// this has to be called everytime shape change, or a hole/wall is activated/deactivated.
void ShortestPath::updateGraph() {
    // step 1. get all the edges for LOS test
    // edges include:
    //   - outline edges
    //   - active hole edges
    //   - walls
    //
    // step 2. add all nodes. For each node, check LOS with all other nodes
    // nodes include:
    //   - concave outline nodes
    //   - convex hole nodes
    //   - internal wall nodes

    // step 1.
    m_graph = std::make_shared<Graph<int, glm::vec2>>();
    m_graphNoWalls = std::make_shared<Graph<int, glm::vec2>>();

    m_edges.clear();
    auto outline = m_shape->getOutlineVertices();
    for (size_t i = 0; i < outline.size(); ++i) {
        m_edges.push_back({outline[i], outline[(i+1) % outline.size()], false});
    }
    for (size_t i = 0; i < m_shape->getHoleCount(); ++i) {
        if (m_inactiveHoles.count(i) == 0) {
            outline = m_shape->getHoleVertices(i);
            for (size_t j = 0; j < outline.size(); ++j) {
                m_edges.push_back({outline[j], outline[(j + 1) % outline.size()], false});
            }
        }
    }
    for (const auto& wall : m_walls) {
        if (wall.active) {
            m_edges.push_back({wall.A, wall.B, true});
        }
    }

    // step 2.
    outline = m_shape->getOutlineVertices();
    addPoly(outline);
    for (int i = 0; i < m_shape->getHoleCount(); ++i) {
        if (m_inactiveHoles.count(i) == 0) {
            addPoly(m_shape->getHoleVertices(i), -1.0f);
        }
    }
    for (const auto& wall : m_walls) {
        if (m_shape->isPointInside(glm::vec3(wall.A, 0.0f))) {
            addNode(wall.A);
        }
        if (m_shape->isPointInside(glm::vec3(wall.B, 0.0f))) {
            addNode(wall.B);
        }
    }


}

void ShortestPath::setShape(std::shared_ptr<IShape> shape) {
    m_shape = std::dynamic_pointer_cast<Polygon>(shape);
    if (m_shape == nullptr) {
        GLIB_FAIL("A polygon is required in shortestPath")
    }
    updateGraph();
//    auto& vertices = m_shape->getOutlineVertices();
//    for (int i = 0; i < vertices.size(); ++i) {
//        glm::vec2 a = vertices[i];
//        glm::vec2 b = vertices[(i+1)%vertices.size()];
//        m_edges.emplace_back(a, b);
//    }
//    for (int i = 0; i < m_shape->getHoleCount(); ++i) {
//        if (m_inactiveHoles.count(i) == 0) {
//            const auto& vertices = m_shape->getHoleVertices(i);
//            for (int i = 0; i < vertices.size(); i++) {
//                float t = 0, u = 0;
//                if (segmentIntersection(point, P, vertices[i], vertices[i+1 % vertices.size()], t, u) && (t > eps && t < 1.0f - eps)) {
//                    intersection = true;
//                    break;
//                }
//            }
//        }
//    }
//
//    auto type = m_shape->getShapeType();
//
//    std::cout << "nodes\n-----\n";
//    for (const auto& node : m_graph->getNodes()) {
//        std::cout << node.first << ": " << node.second.x << ", " << node.second.y << "\n";
//    }
//    std::cout << "edges\n-----\n";
//    for (const auto& e : m_graph->getEdges()) {
//        for (const auto& edge : e.second) {
//            std::cout << e.first << " --> " << edge.first << " (" << edge.second << ")\n";
//        }
//    }
    //exit(1);
}

int ShortestPath::find(glm::vec2 start, glm::vec2 end, std::vector<glm::vec2> &path) {
    // finds the shortest path between start and end points. Place all intermediate points in path

    // 1. If start, or end point, is outside of the shape, then we use their closest point to the edge
    //    of the shape
    glm::vec2 p0 = start;
    glm::vec2 p1 = end;
    if (!m_shape->isPointInside(glm::vec3(start, 0.0f))) {
        auto& algo = ClosestPointOnEdge::get();
        p0 = algo.find(start, m_shape.get());
    }
    // if target point is not in shape
    if (!m_shape->isPointInside(glm::vec3(end, 0.0f))) {
        auto& algo = ClosestPointOnEdge::get();
        p1 = algo.find(end, m_shape.get());
    }
    // if p0 == p1, nothing to do
    if (glm::length(p0 - p1) < 0.01f) {
        return 0;
    }

    // now we need to add p0 and p1 to the graph
    int istart = addNode(p0);
    int iend = addNode(p1);
    // TODO stuff
    std::vector<int> pth;
    auto dist = m_graph->shortestPath(istart, iend, pth);
    bool hasFreePath = true;
    if (dist == std::numeric_limits<float>::infinity()) {
        // try to go to another point. Remove walls and see if now we have a path
        hasFreePath = false;
        dist = m_graphNoWalls->shortestPath(istart, iend, pth);
    }
    if (dist != std::numeric_limits<float>::infinity()) {
        // stop when you hit a wall!
        auto current = m_graph->getNode(pth.back());
        path.push_back(current);
        for (int i = pth.size()-2; i >= 0; --i) {
            auto nextPoint = m_graph->getNode(pth[i]);
            if (!hasFreePath) {
                float t = 0, u = 0;
                float wallHit = 2.0f;
                bool hitsWall = false;
                glm::vec2 wdir;
                for (const auto &wall : m_edges) {
                    if (wall.wallEdge) {
                        segmentIntersection(current, nextPoint, wall.A, wall.B, t, u);
                        if (t >= 0.0f && t <= wallHit) {
                            wallHit = t;
                            hitsWall = true;
                            wdir = glm::normalize(wall.B-wall.A);
                        }
                    }
                }
                if (hitsWall) {
                    glm::vec2 ciao = glm::normalize(nextPoint-current);
                    float cangle = glm::angle(wdir, ciao);
                    glm::vec2 pdest =current + t * (nextPoint-current) - (2.0f * m_eps / sin(cangle))*ciao;
                    path.push_back(pdest);
                    break;
                }
            }
            path.push_back(nextPoint);
        }
//        for (auto iter = pth.rbegin(); iter != pth.rend(); iter++) {
//            path.push_back(m_graph->getNode(*iter));
//
//        }
    }
    removeNode(istart);
    removeNode(iend);
    return (hasFreePath ? 0 : 1);
    //m_graph->removeNode(istart);
    //m_graph->removeNode(iend);

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

const std::vector<Wall> & ShortestPath::getWalls() const {
    return m_walls;
}