#pragma once

#include <monkey/math/compound.h>

// Tessellated holes. At the moment holes not included, but TODO add holes
// The polygon is triangulated
class PolyTri : public CompoundShape {
public:
    PolyTri(const ITable&);
    std::string toString() const override;
    std::vector<glm::vec2> getPoints() override;

    void accept (AcyclicVisitor& v) override;
private:
    std::vector<glm::vec2> m_points;
    std::vector<uint32_t> m_tri;
};

