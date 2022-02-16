#include <monkey/math/shapes3d/pseudo3d.h>
#include <monkey/engine.h>
#include <monkey/scenefactory.h>

Pseudo3DShape::Pseudo3DShape(const ITab& t) {
    m_type = ShapeType::PSEUDO3D;
    auto shape = t["shape"];
    m_internalShape = Engine::get().GetSceneFactory()->make2<IShape>(*shape.get());
    m_halfDepth = t.get<float>("half_depth");
    m_bounds = m_internalShape->getBounds();
    m_bounds.min.z = -m_halfDepth;
    m_bounds.max.z = m_halfDepth;

}

bool Pseudo3DShape::isPointInside(glm::vec3 p) const {
    if (fabs(p.z) > m_halfDepth) {
        return false;
    }
    return m_internalShape->isPointInside(p);
}

IShape * Pseudo3DShape::getInternalShape() {
    return m_internalShape.get();
}