#include <monkey/math/shapes3d/prism.h>
#include <monkey/engine.h>


Prism::Prism(const ITab & t) {
	m_type = ShapeType::PRISM;

	auto factory = Engine::get().GetSceneFactory();
	m_height = t.get<float>("height");

    auto sh = t["shape"];
    m_shape = factory->make2<IShape>(*sh);
    m_bounds = m_shape->getBounds();
    m_bounds.max.z = -m_bounds.min.y;
	m_bounds.min.z = -m_bounds.max.y;
	m_bounds.min.y = 0;
	m_bounds.max.y = m_height;


}

IShape * Prism::getBaseShape() const {
	return m_shape.get();
}