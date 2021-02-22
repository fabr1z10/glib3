#include <monkey/math/algo3d/geometry.h>

CollisionReport intersectSegmentPlane(const Segment3D& s, const Plane& p)
{
	CollisionReport report;
	// Compute the t value for the directed line ab intersecting the plane
	glm::vec3 ab = s.getB() - s.getA();
	auto n = p.getNormal();
	auto d = p.getDistance();
	float t = (d - glm::dot(n, s.getA())) / glm::dot(n, ab);
	// If t in [0..1] compute and return intersection point
	if (t >= 0.0f && t <= 1.0f) {
		report.collide = true;
		report.distance = t;
		//report.c = t;
		//report.a = s.a + t * ab;
		return report;
	}
	// Else no intersection
	return report;
}
