#pragma once

#include "monkey/math/shapes/convexpoly.h"

// oriented 2d box
class Rect : public IConvexPolygon {
public:
    Rect(float width, float height, glm::vec3 offset=glm::vec3(0.0f));
    explicit Rect(const ITable&);
    //std::unique_ptr<IShape> transform (const glm::mat4& t) override;

    float getWidth() const;
    float getHeight() const;
    bool isPointInside(glm::vec3) const override;
    //void accept (AcyclicVisitor& v) override;

    glm::vec2 project(glm::vec2 axis, const glm::mat4& t) const override;
    //std::vector<glm::vec2> getPoints() override;
    std::vector<glm::vec2> getEdges() const override;
    std::vector<glm::vec2> getVertices() const override;

private:
    float m_width;
    float m_height;
    glm::vec2 m_u, m_v;
    void initBounds();
};

inline float Rect::getWidth() const {
    return m_width;
}

inline float Rect::getHeight() const {
    return m_height;
}