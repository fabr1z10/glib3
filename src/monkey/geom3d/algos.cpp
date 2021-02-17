#include <monkey/geom3d/algos.hpp>
#include <monkey/math/geom.h>
#include <monkey/geom3d/shapes.hpp>

using namespace geom3d;

CollisionReport geom3d::intersectSegmentPlane(const Segment& s, const Plane& p)
{
    CollisionReport report;
    // Compute the t value for the directed line ab intersecting the plane
    glm::vec3 ab = s.b - s.a;
    float t = (p.d - glm::dot(p.n, s.a)) / glm::dot(p.n, ab);
    // If t in [0..1] compute and return intersection point
    if (t >= 0.0f && t <= 1.0f) {
        report.collide = true;
        report.c = t;
        report.a = s.a + t * ab;
        return report;
    }
    // Else no intersection
    return report;
}

// Given planes p1 and p2, compute line L = p+t*d of their intersection.
// Return 0 if no such line exists
CollisionReport geom3d::intersectPlanes(const Plane& p1, const Plane& p2)
{
    // Compute direction of intersection line
    CollisionReport report;
    glm::vec3 d = glm::cross(p1.n, p2.n);
    // If d is (near) zero, the planes are parallel (and separated)
    // or coincident, so they’re not considered intersecting
    float denom = glm::dot(d, d);
    if (denom < eps) return report;
    // Compute point on intersection line
    report.collide = true;
    report.a = d;
    report.b = glm::cross(p1.d*p2.n - p2.d*p1.n, d) / denom;
    return report;
}

// Intersect ray R(t) = p + t*d against AABB a. When intersecting,
// return intersection distance tmin and point q of intersection
CollisionReport geom3d::intersectSegmentAABB(const Segment& s, const geom3d::AABox& a) {
    glm::vec3 p = s.a;
    glm::vec3 d = glm::normalize(s.b - s.a);
    CollisionReport report;
    float tmin = 0.0f; // set to -FLT_MAX to get first hit on line
    float tmax = FLT_MAX; // set to max distance ray can travel (for segment)
    // For all three slabs
    for (int i = 0; i < 3; i++) {
        if (fabs(d[i]) < eps) {
            // Ray is parallel to slab. No hit if origin not within slab
            if (p[i] < a.min[i] || p[i] > a.max[i]) return report;
        } else {
            // Compute intersection t value of ray with near and far plane of slab
            float ood = 1.0f / d[i];
            float t1 = (a.min[i] - p[i]) * ood;
            float t2 = (a.max[i] - p[i]) * ood;
            // Make t1 be intersection with near plane, t2 with far plane
            if (t1 > t2) std::swap(t1, t2);
            // Compute the intersection of slab intersection intervals
            if (t1 > tmin) tmin = t1;
            if (t2 > tmax) tmax = t2;
            // Exit with no collision as soon as slab intersection becomes empty
            if (tmin > tmax) return report;
        }
    }
    // Ray intersects all 3 slabs. Return point (q) and intersection t value (tmin)
    report.collide = true;
    report.c = tmin;
    report.a = p + d * tmin;
    return report;
}


// Test if AABB b intersects plane p
CollisionReport geom3d::TestAABBPlane(const AABox& b, const Plane& p) {
    // Convert AABB to center-extents representation
    glm::vec3 c = (b.max + b.min) * 0.5f; // Compute AABB center
    glm::vec3 e = b.max - c; // Compute positive extents

    // Compute the projection interval radius of b onto L(t) = b.c + t * p.n
    float r = e[0]* fabs(p.n[0]) + e[1]* fabs(p.n[1]) + e[2] * fabs(p.n[2]);

    // Compute distance of box center from plane
    float s = glm::dot(p.n, c) - p.d;

    // Intersection occurs when distance s falls within [-r,+r] interval
    CollisionReport report;
    report.collide = (fabs(s) <= r);
    return report;
}
// set to max distance ray can travel (for segment)

CollisionReport geom3d::TestAABBAABB(const AABox& a, const AABox& b)
{
    // Exit with no intersection if separated along an axis
    CollisionReport report;
    if (a.max[0] < b.min[0] || a.min[0] > b.max[0]) return report;
    if (a.max[1] < b.min[1] || a.min[1] > b.max[1]) return report;
    if (a.max[2] < b.min[2] || a.min[2] > b.max[2]) return report;
    // Overlapping on all axes means AABBs are intersecting
    report.collide = true;
    return report;
}