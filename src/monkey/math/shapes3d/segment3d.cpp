#include <monkey/math/shapes3d/segment3d.h>

Segment3D::Segment3D(glm::vec3 A, glm::vec3 B) : IShape(), a(A), b(B) {
	initBounds();
}


Segment3D::Segment3D(const ITab& t) : IShape(t) {
	a = t.get<glm::vec3>("a");
	b = t.get<glm::vec3>("b");
	initBounds();
}

void Segment3D::initBounds() {
	for (int i = 0; i < 3; ++i) {
		if (a[i] <= b[i]) {
			m_bounds.min[i] = a[i];
			m_bounds.max[i] = b[i];
		} else {
			m_bounds.min[i] = b[i];
			m_bounds.max[i] = a[i];
		}
	}
}
//
//std::unique_ptr<IShape> Segment3D::transform(const glm::mat4 & m) {
//	auto ap = m * glm::vec4(a, 1.0f);
//	auto bp = m * glm::vec4(b, 1.0f);
//	return std::make_unique<Segment3D>(ap, bp);
//}

bool Segment3D::isPointInside(glm::vec3 P) const {
	return false; // TODO
}

