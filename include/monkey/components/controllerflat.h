#pragma once

#include <monkey/components/icontroller.h>
#include <glm/glm.hpp>

class ICollisionEngine;

class ControllerFlat : public IController {
public:
	ControllerFlat(const ITab&);
	virtual ~ControllerFlat() = default;
	void Start() override;
	void Begin() override;
	void Update(double) override {}
	void Move(glm::vec3&) override;
	std::type_index GetType() override;
	bool grounded() const { return false; }
	bool ceiling () const { return false; }
	bool side () const { return false; }

private:
    void drawShape() override;

    void HorizontalCollisions(glm::vec2& velocity);
	void VerticalCollisions(glm::vec2& velocity);
	Entity* m_platform;
	ICollisionEngine * m_collision;
	//int m_collisionMaskDown;
	//int m_collisionMaskAny;
	int m_horizontalRayCount;
	int m_verticalRayCount;
	float m_horizontalRaySpacing;
	float m_verticalRaySpacing;
	float m_skinWidth;
	int m_mask;
	glm::vec2 m_size;
};

inline std::type_index ControllerFlat::GetType() {
	return std::type_index(typeid(IController));
}

