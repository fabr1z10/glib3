#include <monkey/math/algo/geometry.h>
#include <monkey/math/shapes/compound.h>

bool triangleIsCCW(const glm::vec2& a, const glm::vec2& b, const glm::vec2& c) {
    float det = ((a.x - c.x) * (b.y - c.y)) - ((a.y - c.y) * (b.x - c.x));
    return det > 0;
}

int pointInConvexPolygon(glm::vec2 p, const std::vector<glm::vec2>& v)
{
    int n = v.size();
    // Do binary search over polygon vertices to find the fan triangle
    // (v[0], v[low], v[high]) the point p lies within the near sides of
    int low = 0, high = n;
    do {
        int mid = (low + high) / 2;
        if (triangleIsCCW(v[0], v[mid], p))
            low = mid;
        else
            high = mid;
    } while (low + 1 < high);
    // If point outside last (or first) edge, then it is not inside the n-gon
    if (low == 0 || high == n) return 0;
    // p is inside the polygon if it is left of
    // the directed edge from v[low] to v[high]
    return triangleIsCCW(v[low], v[high], p);
}

glm::vec2 project(const std::vector<glm::vec2>& points, const glm::vec2& axis, const glm::mat4& t) {
    glm::vec2 out (std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity());
    for (const auto& p : points) {
    	glm::vec2 pw = t * glm::vec4(p, 0.0f, 1.0f);
        float pr = glm::dot (pw, axis);
        out.x = std::min (out.x, pr);
        out.y = std::max (out.y, pr);
    }
    return out;
}


CollisionReport circleVsCircle(const Circle& c1, const Circle& c2, const glm::mat4& t1, const glm::mat4& t2) {
    CollisionReport report;
    glm::vec2 c1w = t1 * glm::vec4(c1.getOffset(), 1.0f);
	glm::vec2 c2w = t2 * glm::vec4(c2.getOffset(), 1.0f);
    glm::vec2 ab = c2w - c1w;
    float rsum = c1.getRadius() + c2.getRadius();
    float d2 = ab.x * ab.x + ab.y * ab.y;
    report.collide = (d2 < (rsum * rsum));
    return report;
}

CollisionReport shapeVsCompound(const IShape& c1, const CompoundShape& c2, const glm::mat4&, const glm::mat4&) {
	for (const auto& shape : c2.getShapes()) {

	}
}