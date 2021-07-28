#include <monkey/math/raycast3d.h>
#include <monkey/math/shapes3d/prism.h>
#include <glm/gtx/norm.hpp>
#include <monkey/math/geom.h>

RayCast3D::RayCast3D() {

	m_raycasters[ShapeType::AABB] = [&] (glm::vec3 O, glm::vec3 dir, float len, IShape* s, const glm::mat4& t) {
		return this->rayVsAABB(O, dir, len, s, t);
	};
	m_raycasters[ShapeType::PRISM] = [&] (glm::vec3 O, glm::vec3 dir, float len, IShape* s, const glm::mat4& t) {
		return this->rayVsPrism(O, dir, len, s, t);
	};
}

RayCastHit RayCast3D::run(glm::vec3 A, glm::vec3 B, IShape* shape, const glm::mat4& t)  {
	throw;
}

RayCastHit RayCast3D::run(glm::vec3 O, glm::vec3 dir, float length, IShape *shape, const glm::mat4& t) {
	//glm::vec2 A(O);
	//glm::vec2 B = O + dir * length;
	RayCastHit out;
	auto it = m_raycasters.find(shape->getShapeType());
	if (it == m_raycasters.end()) {
		return out;
	}

	out = it->second(O, dir, length, shape, t);
//	if (out.collide) {
//		// here length is just a number between 0 and 1, so it must be scaled to the proper length
//		out.length *= length;
//	}
	return out;

}

RayCastHit RayCast3D::rayVsPrism(glm::vec3 O, glm::vec3 dir, float len, IShape *prism, const glm::mat4 & t) {
	RayCastHit out;
	auto* pr = static_cast<Prism*>(prism);
	// project ray onto xz plane
	auto baseShape = pr->getBaseShape();
	float height = pr->getHeight();
	glm::vec3 ep = O + dir * len;

	// transform points from world to local
	auto invt = glm::inverse(t);
	auto Op = invt * glm::vec4(O, 1.0f);
	auto epp = invt * glm::vec4(ep, 1.0f);
	glm::vec3 ot(Op.x, -Op.z, 0.0f);
	glm::vec3 et(epp.x, -epp.z, 0.0f);
	auto oInside = baseShape->isPointInside(ot);
	auto eInside = baseShape->isPointInside(et);
	if (isZero(glm::length2(ot-et))) {
	    if (oInside) {
	        if (Op.y > height && epp.y > height || Op.y < 0 && epp.y < 0) {
	            return out;
	        }
	        if (Op.y > height) {
	            out.collide = true;
	            out.normal = monkey::up;
	            out.length = Op.y - height;
	        } else if (Op.y < 0) {
	            out.collide = true;
	            out.normal = monkey::down;
	            out.length = -Op.y;
	        }

	    }
	} else {
        RayCast2D rc;
        auto ce = rc.run(ot, et, baseShape, glm::mat4(1.0f));
        if (ce.collide) {
            // find y at impact point
            auto impactPoint = Op + (epp - Op)* (ce.length / glm::length(et-ot));// ot + glm::normalize(et-ot) * ce.length;
            if (impactPoint.y >= 0 && impactPoint.y <= height) {
                out.collide = true;
                out.normal = ce.normal;
                out.length = ce.length;
            }
            std::cerr << "ici\n";
        }
    }
	return out;
}

RayCastHit RayCast3D::rayVsAABB(glm::vec3 O, glm::vec3 dir, float len,IShape *aabb, const glm::mat4 & t) {
	RayCastHit out;

	auto bounds = aabb->getBounds();
	bounds.Transform(t);

	float inf = std::numeric_limits<float>::infinity();

	RayHit t1 {dir.x == 0.0f ? -inf : (bounds.min.x - O.x) / dir.x, glm::vec3(-1.0f, 0.0f, 0.0f)};					// left edge
	RayHit t2 {dir.x == 0.0f ? inf : (bounds.max.x - O.x) / dir.x, glm::vec3(1.0f, 0.0f, 0.0f)};
	RayHit t3 {dir.y == 0.0f ? -inf : (bounds.min.y - O.y) / dir.y, glm::vec3(0.0f, -1.0f, 0.0f)};
	RayHit t4 {dir.y == 0.0f ? inf : (bounds.max.y - O.y) / dir.y, glm::vec3(0.0f, 1.0f, 0.0f)};
	RayHit t5 {dir.z == 0.0f ? -inf : (bounds.min.z - O.z) / dir.z, glm::vec3(0.0f, 0.0f, -1.0f)};
	RayHit t6 {dir.z == 0.0f ? inf : (bounds.max.z - O.z) / dir.z, glm::vec3(0.0f, 0.0f, 1.0f)};
	RayHit tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
	RayHit tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

	// it tmax < 0, ray (line) is intersecting AABB, but whole AABB is behind us
	if (tmax.t < 0) {
		return out;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin.t > tmax.t) {
		return out;
	}

	out.collide = true;
	if (tmin.t < 0) {
		out.normal = tmax.normal;
		out.length = tmax.t;
	} else {
		out.normal = tmin.normal;
		out.length = tmin.t;
	}
	return out;

}
