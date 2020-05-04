#pragma once

#include <monkey/math/shape.h>

class PolyTri : public Shape {
public:
    PolyTri(const ITable&);
    bool isPointInside (glm::vec3) const override;
    void accept (AcyclicVisitor& v) override;
    std::string toString() const override;

    std::vector<glm::vec2> getEdges() override;

private:
    std::vector <glm::vec2> m_points;
    std::vector <glm::vec2> m_edges;
    std::vector <uint32_t> m_tri;
};

