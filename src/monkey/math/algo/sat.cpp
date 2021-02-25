#include <monkey/math/algo/sat.h>
#include <monkey/math/geomalgo.h>

CollisionReport performSAT(std::unordered_set<glm::vec2>& axesw, const Shape2D& a, const Shape2D& b, const glm::mat4& t1, const glm::mat4& t2) {
    // axes are given in world coordinates
    // since dot products do not depend on coordinate systems, we transform axes from world to local
    CollisionReport report;
    report.distance = std::numeric_limits<float>::infinity();
    for (auto& axis : axesw) {
        glm::vec2 pA = a.project(axis, t1);
        glm::vec2 pB = b.project(axis, t2);
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

CollisionReport SAT(const IConvexPolygon& p1, const IConvexPolygon& p2, const glm::mat4& t1, const glm::mat4& t2)
{
    auto edges1 = p1.getEdges();
    auto edges2 = p2.getEdges();

    std::unordered_set<glm::vec2> axes;
    for (auto& e : edges1) {
    	// transform axis in world coordinates
    	glm::vec2 ew = t1 * glm::vec4(e, 0.0f, 0.0f);
        axes.insert (glm::vec2(-ew.y, ew.x));
    }
    for (auto& e : edges2) {
		glm::vec2 ew = t2 * glm::vec4(e, 0.0f, 0.0f);
        axes.insert (glm::vec2(-ew.y, ew.x));
    }
    // pass the axes in world coordinates
    return performSAT(axes, p1, p2, t1, t2);
}

CollisionReport SATCircle(const IConvexPolygon& p, const Circle& c, const glm::mat4& t1, const glm::mat4& t2) {

    auto edges1 = p.getEdges();
    std::unordered_set<glm::vec2> axes;
    for (auto& e : edges1) {
		glm::vec2 ew = t1 * glm::vec4(e, 0.0f, 0.0f);
        axes.insert (glm::normalize(glm::vec2(-ew.y, ew.x)));
    }

    // get circle center in world coordinates
    glm::vec2 centerw = t2 * glm::vec4(c.getOffset(), 1.0f);
    auto vertices = p.getVertices();
    glm::vec2 extraAxis(0.0f);
    float mind2 = std::numeric_limits<float>::infinity();

	// loop through all points
    for (auto& p : vertices) {
    	glm::vec2 pw = t1 * glm::vec4(p, 0.0f, 1.0f);
        glm::vec2 d = centerw - pw;
        float d2 = d.x * d.x + d.y * d.y;
        if (d2 <= mind2) {
            mind2 = d2;
            extraAxis = d;
        }
    }
    axes.insert (glm::normalize(extraAxis));

    return performSAT(axes, p, c, t1, t2);
}
