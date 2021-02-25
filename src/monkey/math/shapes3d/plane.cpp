#include <monkey/math/shapes3d/plane.h>

Plane::Plane(const ITable& t) : IShape(t) {
	n = t.get<glm::vec3>("n");
	d = t.get<float>("d");

}


bool Plane::isPointInside(glm::vec3 P) const {
	return iszero(d - glm::dot(n, P));
}

// construct a plane given 3 points
std::unique_ptr<Plane> Plane::computePlane(glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
	auto p = std::make_unique<Plane>();
	p->n = glm::normalize(glm::cross(b - a, c - a));
	p->d = glm::dot(p->n, a);
	return p;
}