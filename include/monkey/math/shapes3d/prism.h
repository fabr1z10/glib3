#pragma once

#include <monkey/math/shapes/poly.h>


class Prism : public IShape {
public:
    Prism (const ITab&);
    bool isPointInside (glm::vec3) const override {return false;}

private:
    std::shared_ptr<IShape> m_shape;
    float m_height;
};