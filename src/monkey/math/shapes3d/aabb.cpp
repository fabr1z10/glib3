#include <monkey/math/shapes3d/aabb.h>

AABB::AABB(const ITab& t) : IShape(t) {
	m_type = ShapeType::AABB;
	m_size = t.get<glm::vec3>("size");
	m_bounds.min = m_offset;
	m_bounds.max = m_offset + m_size;

}


bool AABB::isPointInside(glm::vec3 P) const {
	glm::vec3 pl = P - m_offset;
	return !(pl.x > m_size[0] || pl.x < 0 || pl.y > m_size[1] || pl.y < 0 || pl.z > m_size[2] || pl.z < 0);
}

