#include <monkey/math/algo/shortestpath.h>
#include <monkey/math/algo/closest.h>
#include <monkey/math/algo/geometry.h>
#include <monkey/math/geom.h>
#include <glm/gtx/vector_angle.hpp>


PolyLineShortestPath::PolyLineShortestPath() {}

void PolyLineShortestPath::setShape(std::shared_ptr<IShape> shape) {
    m_shape = std::dynamic_pointer_cast<PolyLine>(shape);
    updateGraph();
}

void PolyLineShortestPath::updateGraph() {
    m_graph = std::make_shared<Graph<int, glm::vec2>>();
    m_graphNoWalls = std::make_shared<Graph<int, glm::vec2>>();
    const auto& vertices = m_shape->getVertices();
    for (size_t i = 0; i < vertices.size(); ++i) {
        m_graph->addNode(i, vertices[i]);
        m_graphNoWalls->addNode(i, vertices[i]);
    }
    for (const auto& e : m_shape->getEdges()) {
        glm::vec2 segment = vertices[e[1]] - vertices[e[0]];
        float length = glm::length(segment);
        m_graph->addEdge(e.x, e.y, length);
        m_graphNoWalls->addEdge(e.x, e.y, length);
        m_unitVecs.push_back(PolySeg{vertices[e.x], vertices[e.y], glm::normalize(segment), length, e.x, e.y});
    }
}

std::pair<glm::vec2, int> PolyLineShortestPath::getClosestPoint(glm::vec2 P) {
    glm::vec2 cp;
    int k = -1;
    float minDist = std::numeric_limits<float>::infinity();
    int j = 0;
    for (const auto& u : m_unitVecs) {
        float d = glm::dot(P - u.P0, u.unitVec);
        glm::vec2 c = (d < 0.0f) ? u.P0 : (d > u.length ? u.P1 : u.P0 + u.unitVec * d);
        float dc = glm::length2(P - c);
        if (dc < minDist) {
            cp = c;
            k = j;
            minDist = dc;
        }
        j++;
    }
    return std::make_pair(cp, k);
}

int PolyLineShortestPath::addNode(glm::vec2 P, const PolySeg& seg) {
    int id = m_graph->getVertexCount();
    m_graph->addNode(id, P);
    m_graphNoWalls->addNode(id, P);
    m_graph->addEdge(id, seg.i0, glm::length(P - seg.P0));
    m_graph->addEdge(id, seg.i1, glm::length(P - seg.P1));
    return id;
}

int PolyLineShortestPath::find(glm::vec2 start, glm::vec2 end, std::vector<glm::vec2> &path) {

    auto s0 = getClosestPoint(start);
    auto s1 = getClosestPoint(end);
    // TODO important. if both start and end points are on the same edge, add an extra edge between the two
    // well, actually in this case you can simply return the direct path

    if (s0.second == s1.second && s0.second != -1) {
        if (isZero(glm::length2(s0.first - s1.first))) {
            return 0;
        }
        path.push_back(s0.first);
        path.push_back(s1.first);
        return 0;
    }

    int i1 = addNode(s0.first, m_unitVecs[s0.second]);
    int i2 = addNode(s1.first, m_unitVecs[s1.second]);

    std::vector<int> route;
    auto dist = m_graph->shortestPath(i1, i2, route);
    if (dist != std::numeric_limits<float>::infinity()) {
        for (auto it = route.rbegin(); it != route.rend(); ++it) {
            path.push_back(m_graph->getNode(*it));
        }
    }
    m_graph->removeNode(i1);
    m_graph->removeNode(i2);
    return 0;

}

