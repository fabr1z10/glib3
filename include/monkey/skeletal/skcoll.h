#pragma once


// a skel collider is a rectangle associated to a skeleton that gets transformed
// when skeleton animates.

#include <monkey/components/icollider.h>
#include <monkey/math/shapes/poly.h>

class SkModel;

class SkColl : public ICollider {
public:
	SkColl(const SkColl&);
	SkColl (const ITable&);
	void Start() override;
	void Update(double) override;
	Shape* GetShape() override;
	int GetCollisionTag() const override;
	int GetCollisionFlag() const override;
	int GetCollisionMask() const override;
	std::shared_ptr<Component> clone() const override;
	std::type_index GetType() override;
private:
	Renderer * m_renderer;
	Renderer * m_debugRend;
	glm::vec3 m_offset;
	std::vector<glm::vec2> computePoints(glm::vec2 P0, glm::vec2 P1);
	// the points in model coordinates (rest position)
	glm::vec2 m_P0;
	std::vector<int> jointIds0;
	std::vector<float> weights0;
	glm::vec2 m_P1;
	std::vector<int> jointIds1;
	std::vector<float> weights1;
	float m_width;
	// the convex shape
	std::shared_ptr<Polygon> m_polygon;

	// the skeletal model
	SkModel* m_model;

	Bounds GetStaticBoundsI() const override;
	Bounds GetDynamicBoundsI() const override;
	Entity* m_shapeEntity;
	int m_flag;
	int m_mask;
	int m_tag;


};


inline int SkColl::GetCollisionTag() const {
	return m_tag;
}
inline int SkColl::GetCollisionFlag() const {
	return m_flag;
}
inline int SkColl::GetCollisionMask() const {
	return m_mask;
}