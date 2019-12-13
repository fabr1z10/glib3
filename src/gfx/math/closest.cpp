#define GLM_ENABLE_EXPERIMENTAL
#include <gfx/math/closest.h>
#include <iostream>
#include <glm/gtx/transform.hpp>

glm::vec2 ClosestPointOnEdge::getNearest(
        Polygon& p,                 // shape in local coordinates
        glm::mat4& t,               // local trasnform
        float& bestSoFar,
        glm::vec2 closestPointSoFar) // best in WORLD coords
{
    int n = p.GetVertexCount();
    // transform the point in local coords
    glm::vec2 bestPoint = glm::inverse(t) * glm::vec4(closestPointSoFar, 0.0f, 1.0f);
    int ip = n-1;
    glm::vec2 A(t*glm::vec4(p.GetVertex(ip),0.0f, 1.0f));
    glm::vec2 normal;

    for (int i = 0; i < n; i++) {
        glm::vec2 B (t * glm::vec4(p.GetVertex(i), 0.0f, 1.0f));
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
    glm::vec4 worldPoint = t * glm::vec4(bestPoint,0.0f,1.0f);
    return glm::vec2(worldPoint);
}


void ClosestPointOnEdge::visit(Polygon& p) {
    float b = std::numeric_limits<float>::infinity();
    glm::mat4 I(1.0f);
    glm::vec2 P = getNearest(p, I, b, glm::vec2(0.0f));
    m_result = P;
}

void ClosestPointOnEdge::visit(Poly& p) {
    float b = std::numeric_limits<float>::infinity();
    glm::mat4 I(1.0f);
    auto contour = p.GetPolygon();
    glm::vec2 P = getNearest(*contour, I, b, glm::vec2(0.0f));
    for (const auto& hole : p.getHoles()) {
        glm::vec2 pos = hole.getPosition();
        glm::mat4 t = glm::translate(glm::vec3(pos, 0.0f));
        Polygon* a = hole.getPolygon();
        P = getNearest(*a, t, b, P);

        std::cout << "Find nearest of " << m_P.x << ", " << m_P.y << " on poly  is " << P.x << ", " << P.y << "\n";
    }
    m_result = P;
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
