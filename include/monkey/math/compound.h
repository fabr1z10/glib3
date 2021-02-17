//#pragma once
//
//#include <monkey/math/shape.h>
//#include <memory>
//
//class CompoundShape : public Shape {
//public:
//    CompoundShape() : Shape() {}
//    bool isPointInside(glm::vec3) const override;
//    void accept (AcyclicVisitor& v) override;
//    std::string toString() const override;
//    glm::vec2 project(const glm::vec2 axis, const glm::mat4& worldTransform) override;
//    std::vector<glm::vec2> getPoints() override;
//    std::vector<glm::vec2> getEdges() override;
//    const std::vector<std::shared_ptr<Shape>>& GetShapes();
//    void AddShape (std::shared_ptr<Shape>);
//private:
//    std::vector<std::shared_ptr<Shape>> m_shapes;
//};
//
//inline const std::vector<std::shared_ptr<Shape>>& CompoundShape::GetShapes() {
//    return m_shapes;
//}
//
//
//
