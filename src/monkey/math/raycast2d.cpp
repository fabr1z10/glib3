#include <monkey/math/raycast2d.h>
#include <monkey/math/geom.h>
#include <monkey/math/shapes/convexpoly.h>
#include <monkey/math/shapes/poly.h>

RayCast2D::RayCast2D() {
	m_raycasters[ShapeType::SEGMENT] = [&] (glm::vec2 A, glm::vec2 B, IShape* s, const glm::mat4& t) {
		return this->rayCast<IConvexPolygon, false>(A, B, s, t);
	};
	m_raycasters[ShapeType::RECT] = [&] (glm::vec2 A, glm::vec2 B, IShape* s, const glm::mat4& t) {
		return this->rayCast<IConvexPolygon, true>(A, B, s, t);
	};
	m_raycasters[ShapeType::CONVEXPOLY] = [&] (glm::vec2 A, glm::vec2 B, IShape* s, const glm::mat4& t) {
		return this->rayCast<IConvexPolygon, true>(A, B, s, t);
	};

	m_raycasters[ShapeType::POLY] = [&] (glm::vec2 A, glm::vec2 B, IShape* s, const glm::mat4& t) {
		return this->rayCastPoly(A, B, s, t);
	};

	m_raycasters[ShapeType::AABB] = [&] (glm::vec2 A, glm::vec2 B, IShape* s, const glm::mat4& t) {
		return this->rayVsAABB(A, B, s, t);
	};

}

RayCastHit RayCast2D::rayCastPoly(glm::vec2 A, glm::vec2 B, IShape *s, const glm::mat4 &t) {
    RayCastHit out;
    float u {};

    auto poly = static_cast<Polygon*>(s);
	const auto& vertices = poly->getOutlineVertices();
	for (size_t i = 0; i < vertices.size(); ++i) {
		size_t j = (i == vertices.size()-1 ? 0 : i+1);
		glm::vec2 C = t * glm::vec4(vertices[i], 0.0f, 1.0f);
		glm::vec2 D = t * glm::vec4(vertices[j], 0.0f, 1.0f);
		if (seg2seg (A, B, C, D, u)) {
			// update raycast hit
			updateRaycastHit(out, B-A, D-C, u);
		}
	}
    return out;
}


RayCastHit RayCast2D::run(glm::vec3 A, glm::vec3 B, IShape *shape, const glm::mat4& t) {
	RayCastHit out;
	auto it = m_raycasters.find(shape->getShapeType());
	if (it == m_raycasters.end()) {
		return out;
	}

	out = it->second(A, B, shape, t);
	if (out.collide) {
		// here length is just a number between 0 and 1, so it must be scaled to the proper length
		out.length *= glm::length(B-A);
	}
	return out;

}

RayCastHit RayCast2D::run(glm::vec3 O, glm::vec3 dir, float length, IShape *shape, const glm::mat4& t) {
	glm::vec2 A(O);
	glm::vec2 B = O + dir * length;
	RayCastHit out;
	auto it = m_raycasters.find(shape->getShapeType());
	if (it == m_raycasters.end()) {
		return out;
	}

	out = it->second(A, B, shape, t);
	if (out.collide) {
		// here length is just a number between 0 and 1, so it must be scaled to the proper length
		out.length *= length;
	}
	return out;

}
void RayCast2D::updateRaycastHit(RayCastHit& r, glm::vec2 ray, glm::vec2 line, float u) {
	r.collide = true;
	if (u < r.length) {
		r.length = u;
		// compute normal w.r.t. ray
		glm::vec2 d = glm::normalize(line);
		r.normal = glm::vec3(-glm::normalize(ray - d * glm::dot(ray, d)), 0.0f);
	}
}


bool RayCast2D::seg2seg(glm::vec2 A, glm::vec2 B, glm::vec2 C, glm::vec2 D, float &t) {
	// eq for segment 1 is
	// Ax + t(Bx - Ax) = Cx + u(Dx - Cx)
	// Ay + t(By - Ay) = Cy + u(Dy - Cy)
	// which is
	// t(Bx - Ax) - u(Dx - Cx) = (Cx - Ax)
	// t(By - Ay) - u(Dy - Cy) = (Cy - Ay)
	// solution is
	//      | Cx - Ax    Dx - Cx |
	//      | Cy - Ay    Dy - Cy |
	// t = ------------------------
	//      | Bx - Ax    Dx - Cx |
	//      | By - Ay    Dy - Cy |
	glm::vec2 AB = B - A;
	glm::vec2 CD = D - C;
	float den = cross(AB, CD);
	if (isZero(den)) {
		return false;
	}
	glm::vec2 AC = C - A;
	t = cross(AC, CD) / den;
	return (t >= 0 && t <= 1);
}


RayCastHit RayCast2D::rayVsAABB(glm::vec2 O, glm::vec2 B, IShape *aabb, const glm::mat4 & t) {
	RayCastHit out;

	auto bounds = aabb->getBounds();
	bounds.Transform(t);

	float inf = std::numeric_limits<float>::infinity();
	glm::vec2 dir = glm::normalize(B - O);

	RayHit t1 {dir.x == 0.0f ? -inf : (bounds.min.x - O.x) / dir.x, glm::vec3(-1.0f, 0.0f, 0.0f)};					// left edge
	RayHit t2 {dir.x == 0.0f ? inf : (bounds.max.x - O.x) / dir.x, glm::vec3(1.0f, 0.0f, 0.0f)};
	RayHit t3 {dir.y == 0.0f ? -inf : (bounds.min.y - O.y) / dir.y, glm::vec3(0.0f, -1.0f, 0.0f)};
	RayHit t4 {dir.y == 0.0f ? inf : (bounds.max.y - O.y) / dir.y, glm::vec3(0.0f, 1.0f, 0.0f)};
	RayHit tmin = std::max(std::min(t1, t2), std::min(t3, t4));
	RayHit tmax = std::min(std::max(t1, t2), std::max(t3, t4));

	// it tmax < 0, ray (line) is intersecting AABB, but whole AABB is behind us
	if (tmax.t < 0) {
		return out;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin.t > tmax.t) {
		return out;
	}

	out.collide = true;
	auto len = glm::length(B - O);
	if (tmin.t < 0) {
		out.normal = tmax.normal;
		out.length = tmax.t / len;
	} else {
		out.normal = tmin.normal;
		out.length = tmin.t / len;
	}
	return out;

}
//float RayCast2D::SegmentIntersection(glm::vec2 A, glm::vec2 B, glm::vec2 C, glm::vec2 D) {
//
//    // check if A and B are same side of BC
//    glm::vec2 CD = D - C;
//    float a = cross(C-A, CD);
//    if (sign(a) == sign(cross(C-B, CD)))
//        return std::numeric_limits<float>::infinity();
//
//    glm::vec2 AB = B - A;
//    if (sign(cross (A - C, AB)) == sign(cross(A-D, AB)))
//        return std::numeric_limits<float>::infinity();
//
//    // if we get here, we definitely are intersecting, so let's compute
//    return (a / cross(AB, CD)) * glm::length(AB);
//
//
//}
//
//RayCastHit RayCast2D::SegmentIntersection(glm::vec2 A, glm::vec2 B, std::vector<glm::vec2>& p)
//{
//    p.push_back(p.front());
//    RayCastHit ret;
//    ret.collide = false;
//    ret.length = m_length;
//    for (int i = 1; i < p.size(); ++i) {
//        glm::vec2 Cw (m_transform * glm::vec4(p[i-1], 0.0f, 1.0f));
//        glm::vec2 Dw (m_transform * glm::vec4(p[i], 0.0f, 1.0f));
//        float l = SegmentIntersection(m_A, m_B, Cw, Dw);
//        if (l < ret.length) {
//            ret.collide = true;
//            ret.length = l;
//            ret.normal = glm::vec3(glm::normalize(Perp(Dw-Cw)), 0.0f);
//        }
//    }
//    return ret;
//}
//
//RayCastHit RayCast2D::SegmentIntersectionSimple(glm::vec2 A, glm::vec2 B, std::vector<glm::vec2>& p)
//{
//    p.push_back(p.front());
//    RayCastHit ret;
//    ret.collide = false;
//    ret.length = m_length;
//    for (int i = 1; i < p.size(); ++i) {
//        float l = SegmentIntersection(A, B, p[i-1], p[i]);
//        if (l < ret.length) {
//            ret.collide = true;
//            ret.length = l;
//            ret.normal = glm::vec3(glm::normalize(Perp(p[i]-p[i-1])), 0.0f);
//        }
//    }
//    return ret;
//}
//
//
//void RayCast2D::visit(Line& l) {
//    glm::vec2 Cw (m_transform * glm::vec4(l.getA(), 0.0f, 1.0f));
//    glm::vec2 Dw (m_transform * glm::vec4(l.getB(), 0.0f, 1.0f));
//    float t = SegmentIntersection(m_A, m_B, Cw, Dw);
//    if (t == std::numeric_limits<float>::infinity()) {
//        m_result.collide = false;
//        m_result.length = m_length;
//    } else {
//        m_result.collide = true;
//        m_result.length = t;
//        m_result.normal = glm::vec3(glm::normalize(Perp(Dw-Cw)), 0.0f);
//    }
//}
//
//void RayCast2D::visit(Rect& r) {
//    auto points = r.getPoints();
//    m_result = SegmentIntersection(m_A, m_B, points);
//}
//
//void RayCast2D::visit(Polygon& p) {
//    auto points = p.getPoints();
//    m_result = SegmentIntersection(m_A, m_B, points);
//}
//
//void RayCast2D::visit(Poly & p) {
//    auto cont = p.GetPolygon();
//    auto points = cont->getPoints();
//    m_result = SegmentIntersection(m_A, m_B, points);
//    if (!m_result.collide) {
//
//        const auto& holes = p.getHoles();
//        for (const auto& hole : holes) {
//            //const auto& wt = hole.getWorldTransform();
//            //const auto& iwt = glm::inverse(wt);
//            //glm::vec2 lA (iwt * glm::vec4(m_A, 1.0f));
//            //glm::vec2 lB (iwt * glm::vec4(m_B, 1.0f));
//            auto points = hole.getPolygon()->getPoints();
//
//            m_result = SegmentIntersectionSimple (m_A,m_B, points);
//            if (m_result.collide) {
//                //m_result.normal = glm::vec3(wt * glm::vec4(m_result.normal, 0.0f));
//                return;
//            }
//
//        }
//
//    }
//
//}
//
//
//void RayCast2D::visit(Circle& c) {
//    glm::vec3 C(m_transform * glm::vec4(c.getPoints()[0], 0.0f, 1.0f));
//    glm::vec3 a = m_A - C;
//    glm::vec3 b = m_B - C;
//    float a2 = a.x*a.x + a.y*a.y;
//    float b2 = b.x*b.x + b.y*b.y;
//    float c2 = c.GetRadius() * c.GetRadius();
//    if ((a2 < c2 && b2 < c2) || (a2 > c2 && b2 > c2)) {
//        m_result.collide = false;
//    } else {
//        m_result.collide = true;
//        float a = length2(m_B - m_A);
//        float b = 2.0f * ((m_B.x-m_A.x)*(m_A.x-C.x) + (m_B.y-m_A.y)*(m_A.y-C.y));
//        float c = length2(C - m_A) - c2;
//        m_result.length = GetFirstSolution (a,b,c);
//    }
//}
//
//void RayCast2D::visit(CompoundShape& s) {
//    auto shapes = s.GetShapes();
//    for (auto& c : shapes) {
//        RayCast2D r(m_A, m_dir, m_length, m_transform);
//        c->accept(r);
//        auto pr = r.GetResult();
//        if (pr.collide && (!m_result.collide || m_result.length > pr.length)) {
//            m_result = pr;
//        }
//    }
//}
//
//#include <iostream>
//void RayCast2D::visit(Plane3D& s) {
//    // first, let's transform the ray into obejct coords
//    auto t = glm::inverse(m_transform);
//    glm::vec3 P0 (t * glm::vec4(m_A, 1.0f));
//    glm::vec3 dl (t * glm::vec4(m_dir, 0.0f));
//    float k = -P0.y / dl.y;
//    if (k < 0 || k > m_length) {
//        return;
//    }
//    glm::vec3 ip = P0 + k*dl;
//    if (!s.isPointInside(ip))
//        return;
//    // collision here
//    m_result.length = k;
//    m_result.collide = true;
//    glm::vec3 normal_local = P0.y < 0 ? monkey::down : monkey::up;
//    m_result.normal = glm::vec3(m_transform * glm::vec4(normal_local, 0.0f));
//
//
//}
//
//
//#include <iostream>
//void RayCast2D::visit(Box3D& s) {
//    // first, let's transform the ray into obejct coords
//    auto it = glm::inverse(m_transform);
//    glm::vec3 P0 (it * glm::vec4(m_A, 1.0f));
//    glm::vec3 dl (it * glm::vec4(m_dir, 0.0f));
//    if (s.isPointInside(P0))
//        return;
//    glm::vec3 P1 = P0 +dl*m_length;
//    if (!s.isPointInside(P1))
//        return;
//    float w = s.width();
//    float h = s.height();
//    float d = s.depth();
//    glm::vec3 o = s.GetOffset();
//    // check collision with right face
//    float tm = std::numeric_limits<float>::infinity();
//    glm::vec3 bestNormal;
//    // hit with right side
//    if (dl.x != 0.0f) {
//        float t = ((w + o.x) - P0.x) / dl.x;
//        if (t >= 0 && t <= m_length && t < tm) {
//            tm = t;
//            bestNormal = monkey::right;
//        }
//        t = (o.x - P0.x) / dl.x;
//        if (t >= 0 && t <= m_length && t < tm) {
//            tm = t;
//            bestNormal = monkey::left;
//        }
//    }
//    if (dl.y != 0.0f) {
//        float t = ((h + o.y) - P0.y) / dl.y;
//        if (t >= 0 && t <= m_length && t < tm) {
//            tm = t;
//            bestNormal = monkey::up;
//        }
//        t = (o.y - P0.y) / dl.y;
//        if (t >= 0 && t <= m_length && t < tm) {
//            tm = t;
//            bestNormal = monkey::down;
//        }
//    }
//    if (dl.z != 0.0f) {
//        float t = ((d + o.z) - P0.z) / dl.z;
//        if (t >= 0 && t <= m_length && t < tm) {
//            tm = t;
//            bestNormal = monkey::front;
//        }
//        t = (o.z - P0.z) / dl.z;
//        if (t >= 0 && t <= m_length && t < tm) {
//            tm = t;
//            bestNormal = monkey::back;
//        }
//    }
//    // collision here
//    m_result.length = tm;
//    m_result.collide = true;
//    m_result.normal = glm::vec3(m_transform * glm::vec4(bestNormal, 0.0f));
//
//
//}
