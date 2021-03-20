#pragma once

#include <monkey/math/shape.h>
#include <monkey/math/algo/graph.h>
#include <monkey/math/shapes/poly.h>

//#include <monkey/math/shapes/poly.h>
//#include <monkey/math/shapes/polyline.h>
//
class ShortestPath
{
public:
    ShortestPath ();
    void setShape (std::shared_ptr<IShape>);

    float find(glm::vec2 start, glm::vec2 end, std::vector<glm::vec2>& path);

    //    static std::vector<glm::vec2> Find(Shape&, glm::vec2 A, glm::vec2 B);
//    //void visit(Rect&) override;
//    void visit(Polygon&) override;
//    void visit(Poly&) override;
//    void visit(PolyLine&) override65555555555555555555555555t
private:
    void addPoly(Polygon*, const std::vector<glm::vec2>&, float flip = 1.0f);
    void addNode(Polygon*, glm::vec2);
    std::shared_ptr<Graph<int, glm::vec2>> m_graph;
    std::shared_ptr<IShape> m_shape;
    std::unordered_set<int> m_inactiveHoles;
//    ShortestPath(glm::vec2 A, glm::vec2 B) : m_A{A}, m_B{B} {}
//    glm::vec2 m_A, m_B;
//    std::vector<glm::vec2> m_result;
};
