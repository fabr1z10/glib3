#pragma once

#include "gfx/math/shape.h"

class Circle : public Shape {
public:
    Circle (float radius, glm::vec2 offset =glm::vec2(0.0f)) : Shape(), m_radius(radius), m_offset{offset} {
        m_bounds.min = offset - glm::vec2(m_radius, m_radius);
        m_bounds.max = offset + glm::vec2(m_radius, m_radius);
    }
    bool isPointInside(glm::vec2) const override;
    void accept (AcyclicVisitor& v) override;
    float GetRadius () const;
    glm::vec2 GetOffset() {
        return m_offset;
    }
    std::string toString() const override;
    glm::vec2 project(const glm::vec2 axis, const glm::mat4& worldTransform) override;
    std::vector<glm::vec2> getPoints() override;
    std::vector<glm::vec2> getEdges() override;
private:
    glm::vec2 m_offset;
    float m_radius;
};

inline float Circle::GetRadius () const {
    return m_radius;
}

