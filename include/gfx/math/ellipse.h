#pragma once

#include "gfx/math/shape.h"

class Ellipse : public Shape {
public:
    Ellipse (float xSemiAxis, float ySemiAxis, glm::vec2 offset =glm::vec2(0.0f)) : Shape(), m_xSemiAxis(xSemiAxis), m_ySemiAxis(ySemiAxis), m_offset{offset} {
        m_bounds.min = offset - glm::vec2(m_xSemiAxis, m_ySemiAxis);
        m_bounds.max = offset + glm::vec2(m_xSemiAxis, m_ySemiAxis);
    }
    bool isPointInside(glm::vec2) const override;
    void accept (AcyclicVisitor& v) override;
    glm::vec2 GetSemiAxes () const;
    glm::vec2 GetOffset() {
        return m_offset;
    }
    std::string toString() const override;
    glm::vec2 project(const glm::vec2 axis, const glm::mat4& worldTransform) override;
    std::vector<glm::vec2> getPoints() override;
    std::vector<glm::vec2> getEdges() override;
private:
    glm::vec2 m_offset;
    float m_xSemiAxis;
    float m_ySemiAxis;
};

inline glm::vec2 Ellipse::GetSemiAxes () const {
    return glm::vec2(m_xSemiAxis, m_ySemiAxis);
}


