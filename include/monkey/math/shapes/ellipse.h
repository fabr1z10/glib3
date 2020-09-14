#pragma once

#include <monkey/math/shape.h>

class Ellipse : public Shape {
public:
    Ellipse (float xSemiAxis, float ySemiAxis, glm::vec3 offset =glm::vec3(0.0f)) : Shape(offset), m_xSemiAxis(xSemiAxis), m_ySemiAxis(ySemiAxis) {
        m_bounds.min = offset - glm::vec3(m_xSemiAxis, m_ySemiAxis, 1.0f);
        m_bounds.max = offset + glm::vec3(m_xSemiAxis, m_ySemiAxis, 1.0f);
    }
    Ellipse (const ITable& t);
    bool isPointInside(glm::vec3) const override;
    void accept (AcyclicVisitor& v) override;
    glm::vec2 GetSemiAxes () const;
    std::string toString() const override;
    glm::vec2 project(const glm::vec2 axis, const glm::mat4& worldTransform) override;
    std::vector<glm::vec2> getPoints() override;
    std::vector<glm::vec2> getEdges() override;
private:
    float m_xSemiAxis;
    float m_ySemiAxis;
};

inline glm::vec2 Ellipse::GetSemiAxes () const {
    return glm::vec2(m_xSemiAxis, m_ySemiAxis);
}


