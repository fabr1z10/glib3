#pragma once

#include <monkey/math/shape.h>
#include <memory>

class CompoundShape : public Shape2D {
public:
    CompoundShape() : Shape2D() { m_type = ShapeType::COMPOUND; }
    bool isPointInside(glm::vec3) const override;
//	std::unique_ptr<IShape> transform (const glm::mat4& t) override;

	glm::vec2 project(glm::vec2 axis, const glm::mat4& worldTransform) const override;
//    std::vector<glm::vec2> getPoints() override;
//    std::vector<glm::vec2> getEdges() override;
    const std::vector<std::shared_ptr<Shape2D>>& getShapes() const;
    void addShape (std::shared_ptr<Shape2D>);
private:
    std::vector<std::shared_ptr<Shape2D>> m_shapes;
};

inline const std::vector<std::shared_ptr<Shape2D>>& CompoundShape::getShapes() const {
    return m_shapes;
}
