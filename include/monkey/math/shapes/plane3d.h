#pragma once


#include <monkey/math/shape.h>

class Plane3D : public Shape
{
public:
    Plane3D (float width, float depth, int plane = 0, glm::vec3 bounds = glm::vec3(0.0f));
    Plane3D (const ITable&);
    float width() const;
    float height() const;
    int plane() const;
    bool isPointInside(glm::vec3) const override;
    void accept (AcyclicVisitor& v) override;
    std::string toString() const override {throw;}
    glm::vec2 project(const glm::vec2 axis, const glm::mat4& worldTransform) override {throw;}
    std::vector<glm::vec2> getPoints() override {throw;}
    std::vector<glm::vec2> getEdges() override{throw;}
private:
    float m_width;
    float m_height;
    int m_plane;

};

inline float Plane3D::width() const {
    return m_width;
}

inline float Plane3D::height() const {
    return m_height;
}

inline int Plane3D::plane() const {
    return m_plane;
}