#include <monkey/math/shapes3d/prism.h>
#include <monkey/engine.h>
#include <monkey/scenefactory.h>

Prism::Prism(const ITab & t) {
	m_type = ShapeType::PRISM;

	auto factory = Engine::get().GetSceneFactory();
	m_height = t.get<float>("height");

    auto sh = t["shape"];
    m_shape = factory->make2<IShape>(*sh);
    m_shape->setOffset(m_offset);
    m_bounds = m_shape->getBounds();
    m_bounds.max.z = -m_bounds.min.y;
	m_bounds.min.z = -m_bounds.max.y;
	m_bounds.min.y = -1000.0f;
	m_bounds.max.y = 1000.0f;

	auto walls = t.get<std::vector<int>>("walls", std::vector<int>());
	for (auto wall : walls) {
		m_walls.insert(wall);
	}

}

IShape * Prism::getBaseShape() const {
	return m_shape.get();
}