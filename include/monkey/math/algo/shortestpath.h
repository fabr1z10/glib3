#pragma once

#include <monkey/math/shape.h>
#include <monkey/math/algo/graph.h>
#include <monkey/math/shapes/poly.h>
#include <monkey/math/shapes/polyline.h>

struct Wall {
    glm::vec2 A;
    glm::vec2 B;
    bool active;
};

struct Edge {
    glm::vec2 A;
    glm::vec2 B;
    bool wallEdge;
};



class __attribute__ ((visibility ("default"))) IShortestPath {
public:
    virtual int find(glm::vec2 start, glm::vec2 end, std::vector<glm::vec2>& path) = 0;
    virtual void setShape(std::shared_ptr<IShape>) = 0;
    virtual void updateGraph() = 0;
    void addWall(glm::vec2 A, glm::vec2 B, bool active);
    void setWall(int id, bool active);
    const std::vector<Wall>& getWalls() const;
protected:
    std::vector<Wall> m_walls;
    // keep two graphs, one with walls and one with no walls
    std::shared_ptr<Graph<int, glm::vec2>> m_graph;
    std::shared_ptr<Graph<int, glm::vec2>> m_graphNoWalls;
};


class __attribute__ ((visibility ("default"))) PolygonShortestPath : public IShortestPath
{
public:
    explicit PolygonShortestPath();
    //void setShape (std::shared_ptr<IShape>);

    int find(glm::vec2 start, glm::vec2 end, std::vector<glm::vec2>& path) override;
    void setShape(std::shared_ptr<IShape>) override;
    void updateGraph() override;

private:
    void addPoly(const std::vector<glm::vec2>&, float flip = 1.0f);
    int addNode(glm::vec2);
    void removeNode(int id);

    std::shared_ptr<Polygon> m_shape;
    std::unordered_set<int> m_inactiveHoles;

    std::vector<Edge> m_edges;

    float m_eps;
//    ShortestPath(glm::vec2 A, glm::vec2 B) : m_A{A}, m_B{B} {}
//    glm::vec2 m_A, m_B;
//    std::vector<glm::vec2> m_result;
};


class __attribute__ ((visibility ("default"))) PolyLineShortestPath : public IShortestPath {
public:
    explicit PolyLineShortestPath();
    void setShape(std::shared_ptr<IShape>) override;
    void updateGraph() override;

    int find(glm::vec2 start, glm::vec2 end, std::vector<glm::vec2>& path) override;
private:
    std::pair<glm::vec2, int> getClosestPoint(glm::vec2);
    struct PolySeg {
        glm::vec2 P0, P1;
        glm::vec2 unitVec;
        float length;
        int i0, i1;
    };
    int addNode(glm::vec2 P, const PolySeg& seg);

    std::shared_ptr<PolyLine> m_shape;
    std::vector<PolySeg> m_unitVecs;

};