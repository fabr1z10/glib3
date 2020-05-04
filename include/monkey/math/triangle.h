#pragma once

#include <monkey/math/shape.h>
#include <array>

class Triangle : public Shape {
public:
    // ctor
    Triangle (const glm::vec2& A, const glm::vec2& B, const glm::vec2& C);
    Triangle (const ITable&);
    
    bool isPointInside (glm::vec3) const override;
    void accept (AcyclicVisitor& v) override;
    std::string toString() const override;
    Bounds getBounds() const;
    
    glm::vec2 project(const glm::vec2 axis, const glm::mat4& worldTransform) override;
    std::vector<glm::vec2> getPoints() override;
    std::vector<glm::vec2> getEdges() override;
private:
    std::vector<glm::vec2> m_points;
    std::vector<glm::vec2> m_edges;
    
    
};
