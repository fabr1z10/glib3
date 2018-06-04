#include "graph/poly.h"
#include "graph/geom.h"
#include <gfx/error.h>

bool Polygon::isVertexConcave(int i) const {
    int n = m_points.size();
    glm::vec2 next = m_points[i+1 % n];
    glm::vec2 prev = m_points[i == 0 ? n-1 : i-1];
    glm::vec2 left = prev - m_points[i];
    glm::vec2 right = next - m_points[i];
    float x = cross(left, right);
    return x < 0;
}

bool Polygon::isPointInside(glm::vec2 point) const {
    int i, j;
    bool c = false;
    int nvert = m_points.size();
    for (i = 0, j = nvert-1; i < nvert; j = i++) {
        if ( ((m_points[i].y > point.y) != (m_points[j].y > point.y)) &&
             (point.x < (m_points[j].x-m_points[i].x) * (point.y-m_points[i].y) / (m_points[j].y-m_points[i].y) + m_points[i].x) )
            c = !c;
    }
    return c;
}

bool Polygon::isInLineOfSight(glm::vec2 A, glm::vec2 B) {
    //if (!isPointInside(A) || !isPointInside(B))
     //   return false;
    // checks to see if there's any intersection with the edges
    glm::vec2 P0 = m_points.back();
    for (auto& P1 : m_points) {
        if (LineSegmentCross(A, B, P0, P1))
            return false;
        P0 = P1;
    }
    return true;
}

void Polygon::accept (AcyclicVisitor& v) {
    Visitor<Polygon>* v1 = dynamic_cast<Visitor<Polygon>*>(&v);
    if (v1 != 0)
        v1->visit(*this);
    else
        GLIB_FAIL("not a polygon visitor");
}

bool Poly::isPointInside(glm::vec2 P) const {
    if (!m_polygons[0]->isPointInside(P))
        return false;
    for (int i = 1; i < m_polygons.size(); ++i) {
        if (m_polygons[i]->isPointInside(P))
            return false;
    }
    return true;
}

void Poly::accept (AcyclicVisitor& v) {
    Visitor<Poly>* v1 = dynamic_cast<Visitor<Poly>*>(&v);
    if (v1 != 0)
        v1->visit(*this);
    else
        GLIB_FAIL("not a poly visitor");
}


glm::vec2 Polygon::getNormalAtEdge (int edgeIndex) {
    return glm::normalize(Perp(m_points[(edgeIndex+1) % m_points.size()] - m_points[edgeIndex]));
}

glm::vec2 Polygon::getNormalAtVertex (int i) {
    glm::vec2 a = getNormalAtEdge(i);
    glm::vec2 b = getNormalAtEdge((i-1 >= 0) ? (i-1) : m_points.size()-1);
    return (glm::normalize(0.5f*(a+b)));
    //return glm::normalize(Perp(m_points[(edgeIndex+1) % m_points.size()] - m_points[edgeIndex]));
}

Polygon* Poly::GetPolygon(int i) {
    return m_polygons[i].get();
}

bool Poly::isInLineOfSight(glm::vec2 A, glm::vec2 B) {
    for (auto& p : m_polygons) {
        if (!p->isInLineOfSight(A, B))
            return false;
    }
    return true;
}
//for (i in 0...vertices.length)
//{
//var newPoint:Vector = vertices[i];
//var newSqDist:Float = DistanceSquared(newPoint.x, newPoint.y, point.x, point.y);
//
//if (oldSqDist + newSqDist + 2.0 * Math.sqrt(oldSqDist * newSqDist) - DistanceSquared(newPoint.x, newPoint.y, oldPoint.x, oldPoint.y) < epsilon) {
//return toleranceOnOutside;
//}
//
//var left:Vector;
//var right:Vector;
//if (newPoint.x > oldPoint.x)
//{
//left = oldPoint;
//right = newPoint;
//}
//else
//{
//left = newPoint;
//right = oldPoint;
//}
//
//if (left.x < point.x && point.x <= right.x && (point.y - left.y) * (right.x - left.x) < (right.y - left.y) * (point.x - left.x))
//inside = !inside;
//
//oldPoint = newPoint;
//oldSqDist = newSqDist;
//}
//
//return inside;