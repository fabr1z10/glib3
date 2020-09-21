#pragma once

#include <monkey/math/shape.h>

class PolyChain3D : public Shape
{
public:
    PolyChain3D (const ITable&);
    bool isPointInside(glm::vec3) const override { throw; }
    void accept (AcyclicVisitor& v) override;
    float width() const;
    size_t getPointCount() const;
    glm::vec2 getPoint (size_t) const;
    std::string toString() const override {throw;}
    glm::vec2 project(const glm::vec2 axis, const glm::mat4& worldTransform) override {throw;}
    std::vector<glm::vec2> getPoints() override {throw;}
    std::vector<glm::vec2> getEdges() override {throw;}
private:
    float m_width;
    std::vector<float> m_points;

};

