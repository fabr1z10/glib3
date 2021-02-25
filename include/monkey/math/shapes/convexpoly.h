#pragma once

#include <monkey/math/shape.h>

class IConvexPolygon : public Shape2D {
public:
    IConvexPolygon() : Shape2D() {}
    explicit IConvexPolygon(const ITable& t) : Shape2D(t) {}
    virtual std::vector<glm::vec2> getEdges() const = 0;
    virtual std::vector<glm::vec2> getVertices() const = 0;

};


class ConvexPolygon : public IConvexPolygon {
public:
    explicit ConvexPolygon(const std::vector<glm::vec2>&);
    explicit ConvexPolygon(const ITable&);
    //std::unique_ptr<IShape> transform (const glm::mat4& t) override;
    glm::vec2 project(glm::vec2, const glm::mat4&) const ;

    bool isPointInside(glm::vec3) const override;
    std::vector<glm::vec2> getEdges() const override;
    std::vector<glm::vec2> getVertices() const override;
private:
    void init();
    std::vector<glm::vec2> m_points;
    std::vector<glm::vec2> m_edges;

};

inline std::vector<glm::vec2> ConvexPolygon::getEdges() const {
    return m_edges;
}

inline std::vector<glm::vec2> ConvexPolygon::getVertices() const {
    return m_points;
}
