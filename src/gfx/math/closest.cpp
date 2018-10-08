#include <gfx/math/closest.h>
#include <iostream>

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
            bestPoint = bestPoint - normal*0.01f;
        }
        A = B;
        ip = i;
    }

    return bestPoint;
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
        std::cout << "Find nearest of " << m_P.x << ", " << m_P.y << " on poly " << i << " is " << P.x << ", " << P.y << "\n";
    }
    m_result = P;
    if (std::isnan(m_result.x) || std::isnan(m_result.y)) {
        std::cout << "Probelm hgere \n";
    }
}


void ClosestPointOnEdge::visit(PolyLine& p) {
    const auto& e = p.GetEdges();

    float bestSoFar = std::numeric_limits<float>::infinity();
    glm::vec2 bestPoint;
    for (auto& edge : e) {
        // get closest point on this edge
        glm::vec2 A = edge.first;
        glm::vec2 B = edge.second;
        float l = glm::length(B - A);
        glm::vec2 u = glm::normalize(B - A);
        float d = glm::dot(m_P - A, u);
        glm::vec2 cp = (d > l ? B : (d < 0 ? A : A + u*d));
        // update best point
        float dist = glm::distance(cp, m_P);
        if (dist < bestSoFar) {
            bestSoFar = dist;
            bestPoint = cp;
        }
    }
    m_result = bestPoint;

}

glm::vec2 ClosestPointOnEdge::Find(Shape& s, glm::vec2 P) {
    ClosestPointOnEdge c (P);
    s.accept(c);
    return c.m_result;
}
