#include <monkey/math/shapes3d/aabb.h>

AABB::AABB(const ITable& t) : IShape(t) {
	m_type = ShapeType::AABB;
	m_size = t.get<glm::vec3>("size");
}


bool AABB::isPointInside(glm::vec3 P) const {
	glm::vec3 pl = P - m_offset;
	return !(pl.x > m_size[0] || pl.x < 0 || pl.y > m_size[1] || pl.y < 0 || pl.z > m_size[2] || pl.z < 0);
}
