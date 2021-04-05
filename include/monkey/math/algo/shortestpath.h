#pragma once

#include <monkey/math/shape.h>
#include <monkey/math/algo/graph.h>
#include <monkey/math/shapes/poly.h>

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


class ShortestPath
{
public:
    ShortestPath ();
    void setShape (std::shared_ptr<IShape>);

    float find(glm::vec2 start, glm::vec2 end, std::vector<glm::vec2>& path);
    void updateGraph ();
    void addWall(glm::vec2 A, glm::vec2 B, bool active);
    void setWall(int id, bool active);
    const std::vector<Wall>& getWalls() const;
    //    static std::vector<glm::vec2> Find(Shape&, glm::vec2 A, glm::vec2 B);
//    //void visit(Rect&) override;
//    void visit(Polygon&) override;
//    void visit(Poly&) override;
//    void visit(PolyLine&) override65555555555555555555555555t
private:

    bool pointInPoly(glm::vec2 P);
    void addPoly(const std::vector<glm::vec2>&, float flip = 1.0f);
    int addNode(glm::vec2);
    void removeNode(int id);
    // keep two graphs, one with walls and one with no walls
    std::shared_ptr<Graph<int, glm::vec2>> m_graph;
    std::shared_ptr<Graph<int, glm::vec2>> m_graphNoWalls;
    std::shared_ptr<Polygon> m_shape;
    std::unordered_set<int> m_inactiveHoles;

    std::vector<Edge> m_edges;
    std::vector<Wall> m_walls;
    float m_eps;
//    ShortestPath(glm::vec2 A, glm::vec2 B) : m_A{A}, m_B{B} {}
//    glm::vec2 m_A, m_B;
//    std::vector<glm::vec2> m_result;
};
