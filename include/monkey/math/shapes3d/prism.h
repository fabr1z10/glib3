#pragma once

#include <monkey/math/shapes/poly.h>


class Prism : public IShape {
public:
    Prism (const ITab&);
    bool isPointInside (glm::vec3) const override {return false;}
	IShape* getBaseShape() const;
    float getHeight() const;
    bool isWall(int) const;
private:
    std::shared_ptr<IShape> m_shape;
    std::set<int> m_walls;
    float m_height;
};

inline float Prism::getHeight() const {
	return m_height;
}

inline bool Prism::isWall(int id) const {
	return m_walls.count(id) > 0;
}