#pragma once
//#include <monkey/visitor.h>
#include <monkey/math/shape.h>
//#include <monkey/math/shapes/poly.h>
//#include <monkey/math/shapes/polyline.h>
//#include <monkey/math/shapes/line.h>
//#include <monkey/math/shapes/rect.h>
//#include <monkey/math/shapes/circle.h>
#include <monkey/math/collisionreport.h>
//#include <monkey/math/compound.h>
//
class IRayCast {
public:
	virtual RayCastHit run(glm::vec3 O, glm::vec3 dir, float length, IShape* shape) = 0;
};


class RayCast2D : public IRayCast {
public:
    RayCast2D ();
    RayCastHit run(glm::vec3 O, glm::vec3 dir, float length, IShape* shape) override;
private:
	// test whether AB intersects CD; if they intersect, places in t the
	bool seg2seg(glm::vec2 A, glm::vec2 B, glm::vec2 C, glm::vec2 D, float& t);

	bool rayCastVsCircle (glm::vec2 A, glm::vec2 B, float& t, IShape*);

	void updateRaycastHit(RayCastHit& r, glm::vec2 ray, glm::vec2 line, float t);

	// generic raycast for shapes with vertices
	template<typename T, bool closed>
	RayCastHit rayCast(glm::vec2 A, glm::vec2 B, IShape* s) {
		RayCastHit out;
		T* shape = static_cast<T*>(s);
		float u {};
		bool hit {false};
		const auto& vertices = shape->getVertices();
		for (int i = 1; i < vertices.size(); ++i) {
			if (seg2seg (A, B, vertices[i-1], vertices[i], u)) {
				// update raycast hit
				updateRaycastHit(out, B-A, vertices[i] - vertices[i-1], u);
			}
		}
		if (closed) {
			if (seg2seg(A, B, vertices.back(), vertices.front(), u)) {
				updateRaycastHit(out, B-A, vertices.back() - vertices.front(), u);
			}
		}
		return out;
	}

	std::unordered_map<ShapeType, std::function<RayCastHit(glm::vec2, glm::vec2, IShape*)>> m_raycasters;
};


//
//
//inline RayCastHit RayCast2D::GetResult() {
//    return m_result;
//}