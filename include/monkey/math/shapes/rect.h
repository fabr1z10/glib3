#pragma once

#include "monkey/math/shape.h"

// a rectangle with bottom left corner in offset. Default value for
// offset is the origin.
class Rect : public Shape {
public:
    Rect (float width, float height, glm::vec3 offset=glm::vec3(0.0f)) :
    Shape(offset), m_width(width), m_height(height) {
        initBounds();
    }
    Rect (const LuaTable&);
    Rect (const ITable&);
    bool isPointInside(glm::vec3) const override;
    void accept (AcyclicVisitor& v) override;
    float GetWidth () const;
    float GetHeight () const;

    std::string toString() const override;
    glm::vec2 project(const glm::vec2 axis, const glm::mat4& worldTransform) override;
    std::vector<glm::vec2> getPoints() override;
    std::vector<glm::vec2> getEdges() override;
private:
    void initBounds();
    float m_width;
    float m_height;
};

inline float Rect::GetWidth () const {
    return m_width;
}

inline float Rect::GetHeight () const {
    return m_height;
}
