#include <algorithm>
#include <monkey/math/shapes/compound.h>
#include <monkey/error.h>
#include <monkey/engine.h>
#include <monkey/scenefactory.h>



CompoundShape::CompoundShape(const ITab& t) {
    m_type = ShapeType::COMPOUND;
    auto factory = Engine::get().GetSceneFactory();
    t.foreach("shapes", [&] (const ITab& shape) {
        auto s = factory->make2<IShape>(shape);
        this->addShape(s);
    });
}

bool CompoundShape::isPointInside(glm::vec3 P) const {
    for (auto& shape : m_shapes) {
        if (shape->isPointInside(P))
            return true;
    }
    return false;
}



//glm::vec2 CompoundShape::project(glm::vec2 axis, const glm::mat4& worldTransform) const {
//    glm::vec2 out (std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity());
//    for (const auto& s : m_shapes) {
//        auto p = s->project(axis, worldTransform);
//        out.x = std::min(out.x, p.x);
//        out.y = std::max(out.y, p.y);
//    }
//    return out;
//}
////
//std::vector<glm::vec2> CompoundShape::getPoints() {
//    return std::vector<glm::vec2>();
//}
//
//std::vector<glm::vec2> CompoundShape::getEdges(){
//    return std::vector<glm::vec2>();
//}
//

void CompoundShape::addShape (std::shared_ptr<IShape> s) {
    m_shapes.push_back(s);
    // update the bounding box
    auto b = s->getBounds();
    if (m_shapes.size() == 1) {
        m_bounds = b;
    } else {
        m_bounds.min.x = std::min(m_bounds.min.x, b.min.x);
        m_bounds.min.y = std::min(m_bounds.min.y, b.min.y);
        m_bounds.max.x = std::max(m_bounds.max.x, b.max.x);
        m_bounds.max.y = std::max(m_bounds.max.y, b.max.y);
    }
}
