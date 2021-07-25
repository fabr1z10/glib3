#pragma once
//
//#include <vector>
//#include <memory>
#include "monkey/math/shape.h"
//#include <monkey/math/graph.h>
//
/// A polyline is a polygonal chain i.e. a connected series of line segments
class PolyLine : public IShape {
public:
    PolyLine (const ITab&);
    bool isPointInside (glm::vec3 P) const override;
//    void accept (AcyclicVisitor& v) override;
//    int GetEdgeContaining(glm::vec2 P);
    const std::vector<glm::vec2>& getVertices() const;
    const std::vector<glm::ivec2>& getEdges() const;
//    const std::vector<std::pair<int, int>>& GetEdgeIndices() const;
//    std::string toString() const override;
//    glm::vec2 project(const glm::vec2 axis, const glm::mat4& worldTransform) override {
//        return glm::vec2();
//    }
//    std::vector<glm::vec2> getPoints() override {throw;}
//    std::vector<glm::vec2> getEdges() override{throw;}
//
private:
    std::vector<glm::vec2> m_vertices;
    std::vector<glm::ivec2> m_edgeIndices;
    std::vector<std::pair<glm::vec2, glm::vec2>> m_edges;

};

inline const std::vector<glm::vec2>& PolyLine::getVertices() const {
    return m_vertices;
}

inline const std::vector<glm::ivec2>& PolyLine::getEdges() const{
    return m_edgeIndices;
}

//inline const std::vector<std::pair<int, int>>& PolyLine::GetEdgeIndices() const{
//    return m_edgeIndices;
//}
