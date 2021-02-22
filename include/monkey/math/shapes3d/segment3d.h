#pragma once

#include <monkey/math/shape.h>

class Segment3D : public IShape {
public:
	Segment3D(glm::vec3 A, glm::vec3 B) : IShape(), a(A), b(B) {}
	Segment3D(const ITable& t);
	bool isPointInside (glm::vec3) const override;
	std::unique_ptr<IShape> transform(const glm::mat4&) override;
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
