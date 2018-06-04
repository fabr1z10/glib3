#pragma once

#include <vector>
#include <memory>
#include "shape.h"

// simple polygon (can be concave), no holes
class Polygon : public Shape {
public:
    Polygon (const std::vector<glm::vec2>& p) : m_points{p} {}
    bool isPointInside (glm::vec2 P) const override;
    // tests if segment AB is within the polygon
    bool isInLineOfSight(glm::vec2 A, glm::vec2 B);
    int GetVertexCount() const;
    glm::vec2 GetVertex(int) const;
    bool isVertexConcave (int i) const;
    // gets the outward normal at the j-th index (connecting vertices j to j+1)
    glm::vec2 getNormalAtEdge (int edgeIndex);
    glm::vec2 getNormalAtVertex(int);
    void accept (AcyclicVisitor& v) override;
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

    void AddHole (std::unique_ptr<Polygon> p) {
        m_polygons.push_back(std::move(p));
    }
    bool isPointInside (glm::vec2 P) const override;
    bool isInLineOfSight(glm::vec2 A, glm::vec2 B);
    int GetVertexCount(int polyId = 0) const;
    int GetHoleCount() const;
    int GetPolygonCount() const;
    glm::vec2 GetVertex(int i, int polyId = 0) const;
    bool isVertexConcave (int i, int polyId = 0) const;
    void accept (AcyclicVisitor& v) override;
    Polygon* GetPolygon(int);
private:

    std::vector<std::unique_ptr<Polygon>> m_polygons;
};

inline int Poly::GetVertexCount(int polyId) const { return m_polygons[polyId]->GetVertexCount(); }
inline int Poly::GetHoleCount() const { return m_polygons.size() - 1;}
inline int Poly::GetPolygonCount() const { return m_polygons.size();}
inline glm::vec2 Poly::GetVertex(int i, int polyId) const { return m_polygons[polyId]->GetVertex(i); }