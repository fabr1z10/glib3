#pragma once

#include <monkey/math/shape.h>
#include <memory>

class CompoundShape : public Shape2D {
public:
    CompoundShape() : Shape2D() {}
    bool isPointInside(glm::vec3) const override;
//	std::unique_ptr<IShape> transform (const glm::mat4& t) override;

	//    glm::vec2 project(const glm::vec2 axis, const glm::mat4& worldTransform) override;
//    std::vector<glm::vec2> getPoints() override;
//    std::vector<glm::vec2> getEdges() override;
    const std::vector<std::shared_ptr<IShape>>& getShapes();
    void addShape (std::shared_ptr<IShape>);
private:
    std::vector<std::shared_ptr<IShape>> m_shapes;
};

inline const std::vector<std::shared_ptr<IShape>>& CompoundShape::getShapes() {
    return m_shapes;
}
