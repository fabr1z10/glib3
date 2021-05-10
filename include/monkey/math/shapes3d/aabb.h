#pragma once

#include <monkey/math/shape.h>

class AABB : public IShape {
public:
	AABB(glm::vec3 size, glm::vec3 offset);
	AABB(const ITab& t);
	bool isPointInside (glm::vec3) const override;
	glm::vec3 getSize() const;
private:
	glm::vec3 m_size;

};


inline glm::vec3 AABB::getSize() const {
	return m_size;
}
