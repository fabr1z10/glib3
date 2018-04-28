#include <glm/glm.hpp>
#include <vector>


class Polygon {
public:
    Polygon (const std::vector<glm::vec2>& p) : m_points{p} {}
    bool isPointInside (glm::vec2 P);

private:
    std::vector <glm::vec2> m_points;
};

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
    int GetVertexCount(int polyId = 0) const;
    int GetHoleCount() const;
    glm::vec2 GetVertex(int i, int polyId = 0) const;
    bool isVertexConcave (int i, int polyId = 0) const;

private:

    std::vector<std::vector<glm::vec2>> m_polygons;
};

inline int Poly::GetVertexCount(int polyId) const { return m_polygons[polyId].size(); }
inline int Poly::GetHoleCount() const { return m_polygons.size() - 1;}
inline glm::vec2 Poly::GetVertex(int i, int polyId) const { return m_polygons[polyId][i]; }
