#pragma once

#include <monkey/math/shape.h>

class Segment3D : public IShape {
public:
	Segment3D(glm::vec3 A, glm::vec3 B) : IShape(), a(A), b(B) {}
	Segment3D(const ITab& t);
	bool isPointInside (glm::vec3) const override;
	glm::vec3 getA() const;
	glm::vec3 getB() const;
private:
	glm::vec3 a;
	glm::vec3 b;

};

inline glm::vec3 Segment3D::getA() const {
	return a;
}

inline glm::vec3 Segment3D::getB() const {
	return b;
}
