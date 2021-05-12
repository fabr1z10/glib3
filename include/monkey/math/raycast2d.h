#pragma once

#include "glm/glm.hpp"
#include <monkey/math/shape.h>
//#include <monkey/math/shapes/poly.h>
//#include <monkey/math/shapes/polyline.h>
//#include <monkey/math/shapes/line.h>
//#include <monkey/math/shapes/rect.h>
//#include <monkey/math/shapes/circle.h>
#include <monkey/math/collisionreport.h>//#include <monkey/math/compound.h>
//
class IRayCast {
public:
	virtual RayCastHit run(glm::vec3 O, glm::vec3 dir, float length, IShape* shape, const glm::mat4& t) = 0;
};


class RayCast2D : public IRayCast {
public:
    RayCast2D ();
    RayCastHit run(glm::vec3 O, glm::vec3 dir, float length, IShape* shape, const glm::mat4& t) override;
private:
	struct RayHit {
		float t;
		glm::vec3 normal;
		bool operator< (const RayHit& other) const {
			return t < other.t;
		}
	};
	// test whether AB intersects CD; if they intersect, places in t the
	bool seg2seg(glm::vec2 A, glm::vec2 B, glm::vec2 C, glm::vec2 D, float& t);

	bool rayCastVsCircle (glm::vec2 A, glm::vec2 B, float& t, IShape*, const glm::mat4&);
	RayCastHit rayVsAABB(glm::vec2 A, glm::vec2 B, IShape* aabb, const glm::mat4&);

	void updateRaycastHit(RayCastHit& r, glm::vec2 ray, glm::vec2 line, float t);

	// generic raycast for shapes with vertices
	template<typename T, bool closed>
	RayCastHit rayCast(glm::vec2 A, glm::vec2 B, IShape* s, const glm::mat4& t) {
		RayCastHit out;
		T* shape = static_cast<T*>(s);
		float u {};
		bool hit {false};
		const auto& vertices = shape->getVertices();
		for (int i = 1; i < vertices.size(); ++i) {
			// transform shape vertices from local to world
			glm::vec2 C = t * glm::vec4(vertices[i-1], 0.0f, 1.0f);
			glm::vec2 D = t * glm::vec4(vertices[i], 0.0f, 1.0f);
			if (seg2seg (A, B, C, D, u)) {
				// update raycast hit
				updateRaycastHit(out, B-A, D-C, u);
			}
		}
		if (closed) {
			glm::vec2 C = t * glm::vec4(vertices.back(), 0.0f, 1.0f);
			glm::vec2 D = t * glm::vec4(vertices.front(), 0.0f, 1.0f);
			if (seg2seg(A, B, C, D, u)) {
				updateRaycastHit(out, B-A, D-C, u);
			}
		}
		return out;
	}

	std::unordered_map<ShapeType, std::function<RayCastHit(glm::vec2, glm::vec2, IShape*, const glm::mat4&)>> m_raycasters;
};


//
//
//inline RayCastHit RayCast2D::GetResult() {
//    return m_result;
//}