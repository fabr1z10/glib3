#include <graph/closest.h>

glm::vec2 ClosestPointOnEdge::getNearest(Polygon& p, float& bestSoFar, glm::vec2 closestPointSoFar) {
    int n = p.GetVertexCount();
    glm::vec2 bestPoint = closestPointSoFar;
    int ip = n-1;
    glm::vec2 A = p.GetVertex(ip);
    glm::vec2 normal;
    for (int i = 0; i < n; i++) {

        glm::vec2 B = p.GetVertex(i);
        float l = glm::length(B - A);
        glm::vec2 u = glm::normalize(B - A);
        float d = glm::dot(m_P - A, u);
        glm::vec2 cp = (d > l ? B : (d < 0 ? A : A + u*d));
        // update best point
        float dist = glm::distance(cp, m_P);
        if (dist < bestSoFar) {
            bestSoFar = dist;
            bestPoint = cp;
            normal = (d >= l ? p.getNormalAtVertex(i) : (d <= 0 ? p.getNormalAtVertex(ip) : p.getNormalAtEdge(ip)));
        }
        A = B;
        ip = i;
    }
    m_result = bestPoint - normal*0.01f;
}


void ClosestPointOnEdge::visit(Polygon& p) {
    float b = std::numeric_limits<float>::infinity();
    glm::vec2 P = getNearest(p, b, glm::vec2(0.0f));
    m_result = P;
}

void ClosestPointOnEdge::visit(Poly& p) {
    float b = std::numeric_limits<float>::infinity();
    glm::vec2 P(0.0f);
    for (int i = 0; i < p.GetHoleCount() + 1; ++i) {
        auto poly = p.GetPolygon(i);
        P = getNearest(*poly, b, P);
    }
    m_result = P;
}


glm::vec2 ClosestPointOnEdge::Find(Shape& s, glm::vec2 P) {
    ClosestPointOnEdge c (P);
    s.accept(c);
    return c.m_result;
}