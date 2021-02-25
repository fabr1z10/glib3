#pragma once

#include <monkey/math/shape.h>

class Circle : public Shape2D {
public:
    explicit Circle(float radius, glm::vec3 center =glm::vec3(0.0f));
    explicit Circle(const ITable&);
    //std::unique_ptr<IShape> transform (const glm::mat4& t) override;

    bool isPointInside(glm::vec3) const override;
    //void accept (AcyclicVisitor& v) override;
    float getRadius () const;
    glm::vec2 project(glm::vec2 axis, const glm::mat4&) const override;
//    std::string toString() const override;
//    glm::vec2 project(const glm::vec2 axis, const glm::mat4& worldTransform) override;
//    std::vector<glm::vec2> getPoints() override;
//    std::vector<glm::vec2> getEdges() override;
private:
    float m_radius;
};

inline float Circle::getRadius () const {
    return m_radius;
}

