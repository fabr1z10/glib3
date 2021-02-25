#pragma once

#include <monkey/math/shape.h>

class Plane : public IShape {
public:
	Plane() : n(glm::vec3(0.0f)), d(0.0f) {}
	Plane(const ITable& t);
	bool isPointInside (glm::vec3) const override;
	std::unique_ptr<Plane> computePlane(glm::vec3 a, glm::vec3 b, glm::vec3 c);
	glm::vec3 getNormal() const;
	float getDistance() const;
private:
	glm::vec3 n;    // Plane normal. Points x on the plane satisfy Dot(n,x) = d
	float d;        // distance of the plane from the origin

};

inline glm::vec3 Plane::getNormal() const {
	return n;
}

inline float Plane::getDistance() const {
	return d;
}