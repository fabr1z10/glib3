#define GLM_ENABLE_EXPERIMENTAL
#include <monkey/math/closest.h>
#include <iostream>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/norm.hpp>
#include <monkey/math/geom.h>

void ClosestPointOnEdge::replace(float& d, glm::vec2& bp, float cand, glm::vec2 cp) {
    if (cand < d) {
        d = cand;
        bp = cp;
    }
}

void ClosestPointOnEdge::visit(Rect & rect) {
    // offset is the point at origin
    glm::vec2 offset(rect.GetOffset());
    glm::vec2 localP = m_P - offset;
    float w = rect.GetWidth();
    float h = rect.GetHeight();
    if (rect.isPointInside(glm::vec3(m_P, 0.0f))) {
        glm::vec2 bestPoint = glm::vec2(0.0f, localP.y);
        float dist = localP.x;
        replace (dist, bestPoint, w - localP.x, glm::vec2(w, localP.y));
        replace (dist, bestPoint, localP.y, glm::vec2(localP.x, 0));
        replace (dist, bestPoint, h - localP.y, glm::vec2(localP.x, h));
        m_result = bestPoint;
    } else {
        m_result = glm::vec2(Clamp(localP.x, 0.0f, w), Clamp(localP.y, 0.0f, h));
    }
    m_result += offset;

}

void ClosestPointOnEdge::getNearest(
        Polygon& p,                 // shape in local coordinates
        float& bestSoFar,
        glm::vec2& closestPointSoFar,
        glm::vec2 offset) // best in WORLD coords
{
    int n = p.GetVertexCount();
    // transform the point in local coords
    //glm::vec2 bestPoint = glm::inverse(t) * glm::vec4(closestPointSoFar, 0.0f, 1.0f);
    int ip = n-1;
    glm::vec2 A = p.GetVertex(ip);
    glm::vec2 normal;
    glm::vec2 Pl = m_P - offset;
    for (int i = 0; i < n; i++) {
        glm::vec2 B = p.GetVertex(i);
        float l = glm::length(B - A);
        glm::vec2 u = glm::normalize(B - A);
        float d = glm::dot(Pl - A, u);
        glm::vec2 cp = (d > l ? B : (d < 0 ? A : A + u*d));
        // update best point
        float dist = glm::distance2(cp, Pl);
        if (dist < bestSoFar) {
            bestSoFar = dist;
            closestPointSoFar = cp + offset;
            m_normal = -Perp(u);
            //normal = (d >= l ? p.getNormalAtVertex(i) : (d <= 0 ? p.getNormalAtVertex(ip) : p.getNormalAtEdge(ip)));
            //bestPoint = bestPoint - normal*0.01f;
        }
        A = B;
        ip = i;
    }
}


void ClosestPointOnEdge::visit(Polygon& p) {
    float b = std::numeric_limits<float>::infinity();
    getNearest(p, b, m_result);
}

void ClosestPointOnEdge::visit(Poly& p) {
    float b = std::numeric_limits<float>::infinity();
    Polygon* contour = p.GetPolygon();
    getNearest(*contour, b, m_result);
    for (const auto& hole : p.getHoles()) {
        glm::vec2 pos = hole.getPosition();
        Polygon* a = hole.getPolygon();
        getNearest(*a, b, m_result, pos);
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
    m_normal = glm::vec2(0.0f);
    m_result = bestPoint;

}

ClosestPointResult ClosestPointOnEdge::Find(Shape& s, glm::vec2 P) {
    ClosestPointOnEdge c (P);
    s.accept(c);
    ClosestPointResult result;
    result.normal = c.m_normal;
    result.P = c.m_result;
    return result;
}