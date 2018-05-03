#include <vector>
#include <memory>
#include "shape.h"

// simple polygon (can be concave), no holes
class Polygon : public Shape {
public:
    Polygon (const std::vector<glm::vec2>& p) : m_points{p} {}
    bool isPointInside (glm::vec2 P) const override;
    int GetVertexCount() const;
    glm::vec2 GetVertex(int) const;
    bool isVertexConcave (int i) const;

private:
    std::vector <glm::vec2> m_points;
};

inline int Polygon::GetVertexCount() const {
    return m_points.size();
}

inline glm::vec2 Polygon::GetVertex(int i) const {
    return m_points[i];
}

class Poly : public Shape {
public:
    // defines a polygon without holes
    // Note: the polygons are always clockwise oriented!
    Poly (std::unique_ptr<Polygon> p) { m_polygons.push_back(std::move(p)); }
    Poly (std::unique_ptr<Polygon> p, std::vector<std::unique_ptr<Polygon>> holes) {
        m_polygons.push_back(std::move(p));
        for (auto& hole : holes)
            m_polygons.push_back(std::move(hole));
    }
    bool isPointInside (glm::vec2 P) const override;
    int GetVertexCount(int polyId = 0) const;
    int GetHoleCount() const;
    glm::vec2 GetVertex(int i, int polyId = 0) const;
    bool isVertexConcave (int i, int polyId = 0) const;
private:

    std::vector<std::unique_ptr<Polygon>> m_polygons;
};

inline int Poly::GetVertexCount(int polyId) const { return m_polygons[polyId]->GetVertexCount(); }
inline int Poly::GetHoleCount() const { return m_polygons.size() - 1;}
inline glm::vec2 Poly::GetVertex(int i, int polyId) const { return m_polygons[polyId]->GetVertex(i); }
