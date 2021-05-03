#include <monkey/math/raycast3d.h>

RayCast3D::RayCast3D() {

	m_raycasters[ShapeType::AABB] = [&] (glm::vec3 O, glm::vec3 dir, IShape* s, const glm::mat4& t) {
		return this->rayVsAABB(O, dir, s, t);
	};
}


RayCastHit RayCast3D::run(glm::vec3 O, glm::vec3 dir, float length, IShape *shape, const glm::mat4& t) {
	//glm::vec2 A(O);
	//glm::vec2 B = O + dir * length;
	RayCastHit out;
	auto it = m_raycasters.find(shape->getShapeType());
	if (it == m_raycasters.end()) {
		return out;
	}

	out = it->second(O, dir, shape, t);
//	if (out.collide) {
//		// here length is just a number between 0 and 1, so it must be scaled to the proper length
//		out.length *= length;
//	}
	return out;

}

RayCastHit RayCast3D::rayVsAABB(glm::vec3 O, glm::vec3 dir, IShape *aabb, const glm::mat4 & t) {
	RayCastHit out;

	auto bounds = aabb->getBounds();
	bounds.Transform(t);

	float inf = std::numeric_limits<float>::infinity();

	float t1 = dir.x == 0.0f ? -inf : (bounds.min.x - O.x) / dir.x;
	float t2 = dir.x == 0.0f ? inf : (bounds.max.x - O.x) / dir.x;
	float t3 = dir.y == 0.0f ? -inf : (bounds.min.y - O.y) / dir.y;
	float t4 = dir.y == 0.0f ? inf : (bounds.max.y - O.y) / dir.y;
	float t5 = dir.z == 0.0f ? -inf : (bounds.min.z - O.z) / dir.z;
	float t6 = dir.z == 0.0f ? inf : (bounds.max.z - O.z) / dir.z;
	float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
	float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

	// it tmax < 0, ray (line) is intersecting AABB, but whole AABB is behind us
	if (tmax < 0) {
		return out;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax) {
		return out;
	}

	out.collide = true;
	if (tmin < 0) {
		out.length = tmax;
	} else {
		out.length = tmin;
	}
	return out;

}
