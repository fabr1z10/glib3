#include "graph/geomalgo.h"
#include "graph/geom.h"
#include <algorithm>
#include "graph/shape.h"
#include <gfx/hashpair.h>


CollisionReport SegmentTest(glm::vec2 A, glm::vec2 B, glm::vec2 C, glm::vec2 D) {
    CollisionReport report;
    glm::vec2 r = B - A;
    glm::vec2 s = D - C;
    glm::vec2 PQ = C - A;
    float rxs = cross(r, s);
    if (isEqual(rxs, 0.0f)) {
        // colliner or parallel
        float PQxr = cross(PQ, r);
        if (isEqual(PQxr, 0.0f)) {
            // collinear
            r = glm::normalize(r);
            float a0 = 0.0f;
            float a1 = glm::dot(B - A, r);
            float b0 = glm::dot(PQ, r);
            float b1 = glm::dot(D - A, r);
            float am = std::min(a0, a1);
            float aM = std::max(a0, a1);
            float bm = std::min(b0, b1);
            float bM = std::max(b0, b1);
            if (bm >= aM || bM <= am)
                return report;
            report.collide = true;
            report.direction = r;
            if (aM <= bM) {
                report.direction *= -1.0f;
                report.distance = aM - bm;
            }
            else {
                report.distance = bM - am;
            }
        }
        return report;
    }
    // if we get here then we need to compute t and u
    float t = cross(PQ, s) / rxs;
    float u = cross(PQ, r) / rxs;
    if (t >= 0.0f && t <= 1.0f && u >= 0.0f && u <= 1.0f) {
        // we need to move in the direction of the normal to the 2ns
        glm::vec2 contactPoint = C + u*(D - C);
        glm::vec2 normal = normalize(Perp(s));
        report.collide = true;
        report.direction = normal;
        float pA = dot(A - contactPoint, normal);
        float pB = dot(B - contactPoint, normal);
        // move A or B?
        if (fabs(pA) <= fabs(pB)) {
            report.distance = fabs(pA);
            report.direction *= (pA >= 0 ? -1.0f : 1.0f);
        }
        else {
            report.distance = fabs(pB);
            report.direction *= (pB >= 0 ? -1.0f : 1.0f);
        }
    }
    return report;
}

glm::vec2 Projection (const std::vector<glm::vec2>& points, const glm::vec2& axis, const glm::mat4& t) {
    glm::vec2 out (std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity());
    for (const auto& p : points) {
        glm::vec2 Pw (t * glm::vec4(p, 0.0f, 1.0f));
        float pr = glm::dot (Pw, axis);
        out.x = std::min (out.x, pr);
        out.y = std::max (out.y, pr);
    }
    return out;
}

float ComputeOverlap(glm::vec2& p1, glm::vec2& p2) {
    if (p2.x >= p1.x && p2.x <= p1.y) {
        if (p2.y > p1.y) {
            return -(p1.y - p2.x);
        }
    }
    else if (p1.x >= p2.x && p1.x <= p2.y) {
        if (p1.y > p2.y) {
            return (p2.y - p1.x);
        }
    }
    float a = p2.y - p1.x;
    float b = p1.y - p2.x;
    if (abs(a) < abs(b))
        return a;
    return -b;
}

CollisionReport SAT(std::unordered_set<glm::vec2>& axesw, Shape* a, Shape* b, const glm::mat4& ta, const glm::mat4& tb) {
    // axes are given in world coordinates
    // since dot products do not depend on coordinate systems, we transform axes from world to local
    CollisionReport report;
    report.distance = std::numeric_limits<float>::infinity();
    for (auto& axis : axesw) {
        glm::vec2 pA = a->project(axis, ta);
        glm::vec2 pB = b->project(axis, tb);
        if (pA.x > pB.y || pB.x > pA.y) {
            // we found a non-overlapping axis
            // so we are sure that the two shapes do not collide
            report.collide = false;
            return report;
        }
        // there's overlapping in this axis
        // compute overlap
        float overlap = ComputeOverlap(pA, pB);
        if (fabs(overlap) < fabs(report.distance)) {
            report.distance = fabs(overlap);
            report.direction = axis * (overlap < 0 ? -1.0f : 1.0f);
        }
    }
    // if we get here, it means we haven't found a separating axis.
    // Therefore, we can conclude the two shapes collide
    report.collide = true;
    return report;
}
