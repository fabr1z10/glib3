//#pragma once
//
//
//#include <monkey/math/shape.h>
//
//class ISurf2D : public Shape
//{
//public:
//    ISurf2D (const ITable&);
//    glm::vec2 getMin () const;
//    glm::vec2 getGridSize() const;
//    int getNx() const;
//    int getNy() const;
//    int getPointCount() const;
//    virtual float operator() (float x, float y) = 0;
//    bool isPointInside(glm::vec3) const override {throw; }
//    void accept (AcyclicVisitor& v) override;
//    std::string toString() const override {throw;}
//    glm::vec2 project(const glm::vec2 axis, const glm::mat4& worldTransform) override {throw;}
//    std::vector<glm::vec2> getPoints() override {throw;}
//    std::vector<glm::vec2> getEdges() override{throw;}
//private:
//    glm::vec2 m_min;
//    glm::vec2 m_gridSize;
//    // number of points across x dimension
//    int m_nx;
//    // number of points across y dimension
//    int m_ny;
//};
//
//inline glm::vec2 ISurf2D::getMin() const {
//    return m_min;
//}
//
//inline glm::vec2 ISurf2D::getGridSize() const {
//    return m_gridSize;
//}
//inline int ISurf2D::getNx() const {
//    return m_nx;
//}
//inline int ISurf2D::getNy() const {
//    return m_ny;
//}
//
//class PySurf2D : public ISurf2D {
//
//public:
//    PySurf2D (const ITable&);
//    float operator() (float x, float y) override;
//
//private:
//    pybind11::function m_func;
//
//};