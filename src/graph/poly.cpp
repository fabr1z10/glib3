#include "graph/poly.h"
#include "graph/geom.h"

bool Polygon::isVertexConcave(int i) const {
    int n = m_points.size();
    glm::vec2 next = m_points[i+1 % n];
    glm::vec2 prev = m_points[i == 0 ? n-1 : i-1];
    glm::vec2 left = m_points[i] - prev;
    glm::vec2 right = next - m_points[i];
    float x = cross(left, right);
    return x < 0;
}

bool Polygon::isPointInside(glm::vec2 point) {

    float epsilon = 0.5;

    bool inside = false;

    int n = m_points.size();

    // Must have 3 or more edges
    if (n < 3) return false;

    glm::vec2 oldPoint = m_points[n - 1];
    float oldSqDist = distSq(oldPoint, point);

    for (int i = 0; i < n; ++i) {
        glm::vec2 newPoint = m_points[i];
        float newSqDist = distSq(newPoint, point);
        if (oldSqDist + newSqDist + 2.0 * sqrt(oldSqDist + newSqDist) - distSq(newPoint, oldPoint) < epsilon) {
            return true;
        }
        glm::vec2 left;
        glm::vec2 right;
        if (newPoint.x > oldPoint.x) {
            left = oldPoint;
            right = newPoint;
        } else {
            left = newPoint;
            right = oldPoint;
        }

        if (left.x < point.x && point.x <= right.x &&
            (point.y - left.y) * (right.x - left.x) < (right.y - left.y) * (point.x - left.x))
            inside = !inside;
        oldPoint = newPoint;
        oldSqDist = newSqDist;
    }

    return inside;
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
