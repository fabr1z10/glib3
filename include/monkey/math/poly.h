#pragma once

#include <vector>
#include <list>
#include <memory>
#include "shape.h"

class Entity;

// simple polygon (can be concave), no holes
class Polygon : public Shape {
public:
    Polygon (const std::vector<glm::vec2>& p);
    bool isPointInside (glm::vec3 P) const override;
    // tests if segment AB is within the polygon
    bool isInLineOfSight(glm::vec2 A, glm::vec2 B);
    int GetVertexCount() const;
    glm::vec2 GetVertex(int) const;
    bool isVertexConcave (int i) const;
    // gets the outward normal at the j-th index (connecting vertices j to j+1)
    // ASSUMPTION: vertices are listed in a clockwise order
    glm::vec2 getNormalAtEdge (int edgeIndex) const;
    glm::vec2 getNormalAtVertex(int) const;
    void accept (AcyclicVisitor& v) override;
    std::string toString() const override;
    glm::vec2 project(const glm::vec2 axis, const glm::mat4& worldTransform) override;
    std::vector<glm::vec2> getPoints() override;
    std::vector<glm::vec2> getEdges() override;
private:
    std::vector <glm::vec2> m_points;
};

inline int Polygon::GetVertexCount() const {
    return m_points.size();
}

inline glm::vec2 Polygon::GetVertex(int i) const {
    return m_points[i];
}

struct Hole {
public:
    Hole(glm::vec2 pos, std::shared_ptr<Polygon> p) : position(pos), m_polygon(p) {}
    bool isPointInside (glm::vec3) const;
    bool isVertexConcave (int i) const {
        return m_polygon->isVertexConcave(i);
    }
    int getVertexCount() const {
        return m_polygon->GetVertexCount();
    }
    glm::vec2 getVertex(int i) const;
    glm::vec2 getNormalAtVertex(int i) const;
    bool isInLineOfSight (glm::vec2& A, glm::vec2& B) const;

    Polygon* getPolygon() const;
    glm::vec2 getPosition() const;
    void setPosition (glm::vec2);
private:
    glm::vec2 position;
    std::shared_ptr<Polygon> m_polygon;

};

inline glm::vec2 Hole::getPosition() const {
    return position;
}


inline Polygon* Hole::getPolygon() const {
    return m_polygon.get();
}


class Poly : public Shape {
public:
    // defines a polygon without holes
    // Note: the polygons are always clockwise oriented!
    Poly (std::unique_ptr<Polygon>);
    Poly (const LuaTable&);
    Poly (const ITable&);

    std::string toString() const override;
    // adding and retrieving holes
    // a hole entity must have a hole component
    std::list<Hole>::iterator addHole (glm::vec2 pos, std::shared_ptr<Polygon> poly);
//     {

//    }
    const std::list<Hole>& getHoles() const;
    bool isPointInside (glm::vec3 P) const override;
    bool isInLineOfSight(glm::vec2 A, glm::vec2 B);
    int getVertexCount() const;
    int getHoleCount() const;
    glm::vec2 GetVertex(int i) const;
    bool isVertexConcave (int i, int polyId = 0) const;
    void accept (AcyclicVisitor& v) override;
    Polygon* GetPolygon();
    glm::vec2 project(const glm::vec2 axis, const glm::mat4& worldTransform) override {
        return glm::vec2();
    }
    std::vector<glm::vec2> getPoints() override;
    std::vector<glm::vec2> getEdges() override;

private:
    std::list<Hole> m_holes;
    std::unique_ptr<Polygon> m_contour;
    //std::vector<std::unique_ptr<Polygon>> m_polygons;
};

inline int Poly::getVertexCount() const { return m_contour->GetVertexCount(); }
inline int Poly::getHoleCount() const { return m_holes.size();}
