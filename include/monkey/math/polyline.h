#pragma once

#include <vector>
#include <memory>
#include "shape.h"
#include <monkey/math/graph.h>

// simple polygon (can be concave), no holes
class PolyLine : public Shape {
public:
    PolyLine (const std::vector<glm::vec2>& vertices, const std::vector<std::pair<int, int>>& edges);
    PolyLine (const LuaTable&);
    PolyLine (const ITable&);
    bool isPointInside (glm::vec3 P) const override;
    void accept (AcyclicVisitor& v) override;
    int GetEdgeContaining(glm::vec2 P);
    const std::vector<glm::vec2>& GetVertices() const;
    const std::vector<std::pair<glm::vec2, glm::vec2>>& GetEdges() const;
    const std::vector<std::pair<int, int>>& GetEdgeIndices() const;
    std::string toString() const override;
    glm::vec2 project(const glm::vec2 axis, const glm::mat4& worldTransform) override {
        return glm::vec2();
    }
    std::vector<glm::vec2> getPoints() override {throw;}
    std::vector<glm::vec2> getEdges() override{throw;}

private:
    std::vector<glm::vec2> m_vertices;
    std::vector<std::pair<int, int>> m_edgeIndices;
    std::vector<std::pair<glm::vec2, glm::vec2>> m_edges;

};


inline const std::vector<glm::vec2>& PolyLine::GetVertices() const {
    return m_vertices;
}

inline const std::vector<std::pair<glm::vec2, glm::vec2>>& PolyLine::GetEdges() const{
    return m_edges;
}
inline const std::vector<std::pair<int, int>>& PolyLine::GetEdgeIndices() const{
    return m_edgeIndices;
}
