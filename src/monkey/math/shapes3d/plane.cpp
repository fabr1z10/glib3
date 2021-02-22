#include <monkey/math/shapes3d/plane.h>

Plane::Plane(const ITable& t) : IShape(t) {
	n = t.get<glm::vec3>("n");
	d = t.get<float>("d");

}

std::unique_ptr<IShape> Plane::transform(const glm::mat4 & m) {
	auto plane = std::make_unique<Plane>();
	auto pp = glm::transpose(glm::inverse(m)) * glm::vec4(n, -d);
	plane->n = glm::vec3(pp);
	plane->d = -pp[3];
	return plane;
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