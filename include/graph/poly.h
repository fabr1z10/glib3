#include <glm/glm.hpp>
#include <vector>

class Poly {
public:
    // defines a polygon without holes
    // Note: the polygons are always clockwise oriented!
    Poly (const std::vector<glm::vec2>& p) : m_polygons{p} {}
    Poly (const std::vector<glm::vec2>& p, const std::vector<std::vector<glm::vec2>>& holes) {
        m_polygons.push_back(p);
        for (auto& hole : holes)
            m_polygons.push_back(hole);
    }
    int GetVertexCount() const;
    int GetHoleCount() const;
    glm::vec2 GetVertex(int i, int polyId = 0) const;
private:
    bool isVertexConcave (int i, int polyId = 0);
    std::vector<std::vector<glm::vec2>> m_polygons;
};

inline int Poly::GetVertexCount() const { return m_polygons[0].size(); }
inline int Poly::GetHoleCount() const { return m_polygons.size() - 1;}
inline glm::vec2 Poly::GetVertex(int i, int polyId) const { return m_polygons[polyId][i]; }
