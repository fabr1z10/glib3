#pragma once

#include <monkey/math/shapes/convexpoly.h>

// a segment
class Segment : public IConvexPolygon {
public:
    Segment (glm::vec2 A, glm::vec2 B);
    explicit Segment (const ITab&);
    //std::unique_ptr<IShape> transform (const glm::mat4& t) override;
    glm::vec2 getA() const;
    glm::vec2 getB() const;
    //    bool isPoint    virtual std::unique_ptr<IShape> transform (const glm::mat4& t) = 0;Inside(glm::vec3) const override;
//    void accept (AcyclicVisitor& v) override;
    float getLength() const;
    glm::vec2 getDirection() const;
    bool isPointInside(glm::vec3) const override;
    glm::vec2 project(glm::vec2, const glm::mat4&) const override;

    std::vector<glm::vec2> getEdges() const override;
    std::vector<glm::vec2> getVertices() const override;

private:
    glm::vec2 m_A;
    glm::vec2 m_B;
    glm::vec2 m_dir;
    void initBounds();
};


inline glm::vec2 Segment::getA() const {
    return m_A;
}

inline glm::vec2 Segment::getB() const {
    return m_B;
}
