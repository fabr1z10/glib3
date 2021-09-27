#include <monkey/math/algo/shortestpath.h>
#include <monkey/math/algo/closest.h>
#include <monkey/math/algo/geometry.h>
#include <monkey/math/geom.h>
#include <glm/gtx/vector_angle.hpp>


PolygonShortestPath::PolygonShortestPath() : m_eps(0.01f) {}

void PolygonShortestPath::setShape(std::shared_ptr<IShape> shape) {
    m_shape = std::dynamic_pointer_cast<Polygon>(shape);
    updateGraph();
}

void PolygonShortestPath::updateGraph() {
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

    for (int i = 0; i < outline.size(); ++i) {
        int prev = (i == 0) ? outline.size() - 1 : i-1;
        int next = (i+1) % outline.size();
        m_vertices[i] = Vertex{i, next, prev, outline[i], false};
        m_edges.push_back(Edge{i, next, false});
    }

    for (size_t i = 0; i < m_shape->getHoleCount(); ++i) {
        int offset = m_vertices.size();
        if (m_inactiveHoles.count(i) == 0) {
            outline = m_shape->getHoleVertices(i);
            for (int j = 0; j < outline.size(); ++j) {
                int prev = offset + ((j == 0) ? outline.size() - 1 : j-1);
                int next = offset + ((j+1) % outline.size());
                m_vertices[offset+j] = Vertex{offset+j, next, prev, outline[j], true};
                m_edges.push_back(Edge{offset+j, next, false});
            }
        }
    }

    // step 2.
    createGraph();

    // TODO add back walls
//    for (const auto& wall : m_walls) {
//        if (wall.active) {
//            m_edges.push_back({wall.A, wall.B, true});
//        }
//    }

    // step 2.
//    outline = m_shape->getOutlineVertices();
//    addPoly(outline);
//    for (int i = 0; i < m_shape->getHoleCount(); ++i) {
//        if (m_inactiveHoles.count(i) == 0) {
//            addPoly(m_shape->getHoleVertices(i), -1.0f);
//        }
//    }
    // TODO add back walls
//    for (const auto& wall : m_walls) {
//        if (m_shape->isPointInside(glm::vec3(wall.A, 0.0f))) {
//            addNode(wall.A);
//        }
//        if (m_shape->isPointInside(glm::vec3(wall.B, 0.0f))) {
//            addNode(wall.B);
//        }
//    }
}


int PolygonShortestPath::find(glm::vec2 start, glm::vec2 end, std::vector<glm::vec2> &path) {
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
    int n = m_vertices.size();
    int istart = addNode(n, p0);
    int iend = addNode(n+1, p1);
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
                        auto wA = m_vertices.at(wall.i).P;
                        auto wB = m_vertices.at(wall.j).P;
                        segmentIntersection(current, nextPoint, wA, wB, t, u);
                        if (t >= 0.0f && t <= wallHit) {
                            wallHit = t;
                            hitsWall = true;
                            wdir = glm::normalize(wB - wA);
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

int PolygonShortestPath::addNode(int id, glm::vec2 point) {
    // adds a node to the graph
    // and an edge from the new node to every other node that is in line of sight with it
    //int id = m_graph->getVertexCount();

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

            for (size_t ie = 0; ie < m_edges.size(); ie++) {
                // if either of the point is an END POINT of the current edge, then there's no intersection
                const auto& edge = m_edges[ie];
                if (id == edge.i || id == edge.j || node.first == edge.i || node.first == edge.j) {
                    continue;
                }
                float t = 0, u = 0;
                if (segmentIntersection(point, P, m_vertices.at(edge.i).P, m_vertices.at(edge.j).P, t, u)) {
                    //if ( (dist > m_eps && dist < len - m_eps) ) { //|| ( u > m_eps && u < 1.0f - m_eps)) {
                    if (t > 0 && t < 1 && u > 0 && u < 1) {
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
                bool hasConnectingEdges = false;
                for (const auto& edge : m_edges) {
                    if ((id == edge.i && node.first == edge.j) || (id == edge.j && node.first == edge.i)) {
                        hasConnectingEdges = true;
                        break;
                    }
                }
                auto midPoint = 0.5f * (point + P);
                if (hasConnectingEdges || m_shape->isPointInside(glm::vec3(midPoint, 0.0f))) {
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


void PolygonShortestPath::createGraph() {
    for (const auto& v : m_vertices) {
        const auto& vertex = v.second;
        glm::vec2 edgeNext = m_vertices.at(vertex.next).P - vertex.P;
        glm::vec2 edgePrev = vertex.P - m_vertices.at(vertex.prev).P;
        float flip = vertex.hole ? -1.0f : 1.0f;
        auto f = cross(edgePrev, edgeNext) * flip;
        if (f < 0) {
            addNode(v.first, vertex.P);
        }
    }
}


//void PolygonShortestPath::addPoly(const std::vector<glm::vec2> & outline, float flip) {
//
//    size_t n = outline.size();
//    for (size_t i = 0; i < n; ++i) {
//        size_t inext = (i + 1) % n;
//        size_t iprev = (i == 0) ? n - 1 : i - 1;
//        glm::vec2 v0 = outline[i] - outline[iprev];
//        glm::vec2 v1 = outline[inext] - outline[i];
//        auto f = cross(v0, v1) * flip;
//        // assume outline is specified counterclockwise
//        // therefore a concave vertex
//        if (f < 0) {
//            addNode(outline[i]);
//        }
//
//
//    }
//}

void PolygonShortestPath::removeNode(int id) {
    m_graph->removeNode(id);
    m_graphNoWalls->removeNode(id);
}

