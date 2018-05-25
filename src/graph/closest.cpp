#include <graph/closest.h>


void ClosestPointOnEdge::visit(Polygon& p) {
    int n = p.GetVertexCount();
    float bestDistanceSofar = std::numeric_limits<float>::infinity();
    glm::vec2 bestPoint;
    glm::vec2 A = p.GetVertex(n-1);
    for (int i = 0; i < n; i++) {
        glm::vec2 B = p.GetVertex(i);
        float l = glm::length(B - A);
        glm::vec2 u = glm::normalize(B - A);
        float d = glm::dot(m_P - A, u);
        glm::vec2 cp = (d > l ? B : (d < 0 ? A : A + u*d));
        // update best point
        float dist = glm::distance(cp, m_P);
        if (dist < bestDistanceSofar) {
            bestDistanceSofar = dist;
            bestPoint = cp;
        }
        A = B;
    }
    m_result = bestPoint;
}

glm::vec2 ClosestPointOnEdge::Find(Shape& s, glm::vec2 P) {
    ClosestPointOnEdge c (P);
    s.accept(c);
    return c.m_result;
}