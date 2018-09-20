#pragma once

#include "graph/shape.h"

// a rectangle with bottom left corner in offset. Default value for
// offset is the origin.
class Rect : public Shape {
public:
    Rect (float width, float height, glm::vec2 offset=glm::vec2(0.0f)) :
    Shape(offset), m_width(width), m_height(height) {
        m_bounds.min = offset;
        m_bounds.max = offset + glm::vec2(width, height);
    }
    bool isPointInside(glm::vec2) const override;
    void accept (AcyclicVisitor& v) override;
    float GetWidth () const;
    float GetHeight () const;

    std::string toString() const override;
    glm::vec2 project(const glm::vec2 axis, const glm::mat4& worldTransform) override;
    std::vector<glm::vec2> getPoints() override;
    std::vector<glm::vec2> getEdges() override;

private:
    float m_width;
    float m_height;
};

inline float Rect::GetWidth () const {
    return m_width;
}

inline float Rect::GetHeight () const {
    return m_height;
}
