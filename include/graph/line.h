#pragma once

#include "graph/shape.h"

// a segment
class Line : public Shape {
public:
    Line (glm::vec2 A, glm::vec2 B);
    bool isPointInside(glm::vec2) const override;
    void accept (AcyclicVisitor& v) override;
    float GetLength() const;
    glm::vec2 GetDirection() const;
    std::string toString() const override;
    glm::vec2 getA() const;
    glm::vec2 getB() const;
    glm::vec2 project(const glm::vec2 axis, const glm::mat4& worldTransform) override;
    std::vector<glm::vec2> getPoints() override;
    std::vector<glm::vec2> getEdges() override;
private:
    glm::vec2 m_A;
    glm::vec2 m_B;
    glm::vec2 m_dir;
    float m_length;
    float m_length2;
};

inline float Line::GetLength () const {
    return m_length;
}

inline glm::vec2 Line::GetDirection() const {
    return m_dir;
}

inline glm::vec2 Line::getA() const {
    return m_A;
}

inline glm::vec2 Line::getB() const {
    return m_B;
}
