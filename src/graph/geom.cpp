#include "graph/geom.h"
#include "graph/poly.h"
#include "graph/graph.h"

bool LineSegmentCross (glm::vec2 A, glm::vec2 B, glm::vec2 C, glm::vec2 D) {
    glm::vec2 r = B - A;
    glm::vec2 s = D - C;
    glm::vec2 PQ = C - A;
    float rxs = cross(r, s);
    if (isZero(rxs)) {
        // collinear or parallel
        float PQxr = cross (PQ, r);
        if (isZero(PQxr)) {
            // collinear
            float am = 0;
            float aM = glm::dot(r, r);
            float b0 = glm::dot(PQ, r);
            float b1 = glm::dot(D-A, r);
            if (b0 < b1) {
                return (b0 > aM || am > b1);
            }
            return (b1 > aM || am > b0);
        }
        return false;
    }
    float t = cross(PQ, s) / rxs;
    float u = cross(PQ, r) / rxs;
    return (t > 0.0f && t < 1.0f && u > 0.0f && u < 1.0f);
}

float LineSegmentIntersection (glm::vec2 A, glm::vec2 B, glm::vec2 C, glm::vec2 D) {
    glm::vec2 r = B - A;
    glm::vec2 s = D - C;
    glm::vec2 PQ = C - A;
    float rxs = cross(r, s);
    if (isZero(rxs)) {
        // collinear or parallel
        float PQxr = cross (PQ, r);
        if (isZero(PQxr)) {
            // collinear
            float am = 0;
            float aM = glm::dot(r, r);
            float b0 = glm::dot(PQ, r);
            float b1 = glm::dot(D-A, r);
            if (b0 < b1) {
                return (b0 > aM || am > b1);
            }
            return (b1 > aM || am > b0);
        }
        return false;
    }
    float t = cross(PQ, s) / rxs;
    float u = cross(PQ, r) / rxs;
    if (t > 0.0f && t < 1.0f && u > 0.0f && u < 1.0f)
        return t;
    return -10.0;
}


bool IsBetween (glm::vec2 A, glm::vec2 B, glm::vec2 P, float eps) {
    // first, we need to make sure they are aligned
    float a = cross(B - A, P - A);
    if (fabs(a) > eps)
        return false;
    // if they are aligned, let's get the dot
    float b = glm::dot(P-A, B-A);
    if (b < 0)
        return false;

    if (b > distSq(A, B))
        return false;
    return true;

}


float GetFirstSolution(float a, float b, float c) {
    float delta = b*b - 4*a*c;
    if (delta < 0)
        throw;
    return (-b -sqrt(delta)) / (2.0f*a);
}
//float DistFromSegment (glm::vec2 A, glm::vec2 B, glm::vec2 P) {

//}
//void FindPathInPoly (const Poly& poly, glm::vec2 Start, glm::vec2 End) {
//    int nHoles = poly.GetHoleCount();
//    int nVertices = poly.GetVertexCount();
//    Graph<int, glm::vec2> g;
//    int n = 0;
//    for (int i = 0; i < nVertices; ++i) {
//        if (poly.isVertexConcave(i)) {
//            g.AddNode(n++, poly.GetVertex(i));
//        }
//    }
//
//    // add hole points
//    for (int h = 0; h < nHoles; ++h) {
//        int nvh = poly.GetVertexCount(h+1);
//        for (int j = 0; j < nvh; ++j) {
//            if (!poly.isVertexConcave(j, h+1)) {
//                g.AddNode(n++, poly.GetVertex(j, h+1));
//            }
//        }
//    }
//
//    // add the edges
//    auto keys = g.GetKeys();
//    for (auto iter = keys.begin(); iter != keys.end(); ++iter) {
//        auto iter2 = iter;
//        glm::vec2& v1 = g.GetValue(*iter);
//        for (++iter2; iter2 != keys.end(); ++iter2) {
//            glm::vec2& v2 = g.GetValue(*iter2);
//            if (inLineOfSight(poly, v1, v2)) {
//                g.AddEdge(*iter, *iter2, glm::distance(v1, v2));
//            }
//        }
//
//    }
//
//    g.AddNode(n++, Start);
//    g.AddNode(n++, End);
//
//    // now you need to set up the edges
//
//}

bool inLineOfSight (const Poly& p, glm::vec2 start, glm::vec2 end) {
    
   	float epsilon = 0.5;
    
    // Not in LOS if any of the ends is outside the polygon
    if ( !p.isPointInside(start) || !p.isPointInside(end)) {
        return false;
    }
    
    // In LOS if it's the same start and end location
    if (glm::length(end - start) < epsilon) {
        return false;
    }
    
    // Not in LOS if any edge is intersected by the start-end line segment
   // bool inSight = true;
    int n = p.GetHoleCount() + 1;
    for (int i = 0; i < n; ++i) {
        int m = p.GetVertexCount(i);
        glm::vec2 v1 = p.GetVertex(m-1, i);
        for (int j = 1; j < m; ++j) {
            glm::vec2 v2 = p.GetVertex(j);
            if (LineSegmentCross(start, end, v1, v2)) {
                return false;
            }
            v1 = v2;
        }
    }


    return true;
}
