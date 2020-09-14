#pragma once

#include <monkey/math/shape.h>

class Circle : public Shape {
public:
    Circle (float radius, glm::vec3 offset =glm::vec3(0.0f)) : Shape(offset), m_radius(radius) {
        m_bounds.min = offset - glm::vec3(m_radius, m_radius, 1.0f);
        m_bounds.max = offset + glm::vec3(m_radius, m_radius, 1.0f);
    }
    Circle(const ITable&);
    bool isPointInside(glm::vec3) const override;
    void accept (AcyclicVisitor& v) override;
    float GetRadius () const;

    std::string toString() const override;
    glm::vec2 project(const glm::vec2 axis, const glm::mat4& worldTransform) override;
    std::vector<glm::vec2> getPoints() override;
    std::vector<glm::vec2> getEdges() override;
private:
    float m_radius;
};

inline float Circle::GetRadius () const {
    return m_radius;
}

