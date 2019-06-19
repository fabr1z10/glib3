#pragma once

#include <gfx/component.h>
#include <glm/glm.hpp>


class CollisionEngine;
class ICollider;
class PlatformComponent;

struct CollisionDetails {
	bool above, below;
	bool left, right;
	bool climbingSlope;
	bool descendingSlope;
	glm::vec2 velocityOld;

	float slopeAngle, slopeAngleOld;
	void Reset();
};

inline void CollisionDetails::Reset() {
	above = below = false;
	left = right = false;
	climbingSlope = false;
	descendingSlope = false;
	slopeAngleOld = slopeAngle;
	slopeAngle = 0.0f;
}

struct RaycastOrigins {

	glm::vec2 topLeft, topRight;
	glm::vec2 bottomLeft, bottomRight;
};


class Controller2D : public Component {
public:
	Controller2D(float maxClimbAngle, float maxDescendAngle, float skinwidth = .015f, int horizontalRayCount = 4, int verticalRayCount = 4)
		: Component(), m_maxClimbAngle(maxClimbAngle), m_maxDescendAngle(maxDescendAngle), m_skinWidth(skinwidth), m_horizontalRayCount(horizontalRayCount), m_verticalRayCount(verticalRayCount), m_platform(nullptr) {}
    Controller2D(const Controller2D&);
	virtual ~Controller2D();
	void Start() override;
	void Begin() override;
	bool IsFalling(int);
	void Move(glm::vec2&);
	void ClimbSlope(glm::vec2&, float);
	void DescendSlope(glm::vec2&);
	void CalculateRaySpacing();
	void Update(double) override {}
    void ResetShape(ICollider*);
	//void ForceMove(glm::vec2&);
	CollisionDetails m_details;
	RaycastOrigins m_raycastOrigins;
	using ParentClass = Controller2D;
	void DetachFromPlatform();
	void ForceDetach() { m_platform = nullptr; }
    std::shared_ptr<Component> clone() const override;
	//RayCastHit2D Raycast(glm::vec2 origin, glm::vec2 direction, float length, int mask);
private:
	//std::vector<Collider*> m_ppp;
	void HorizontalCollisions(glm::vec2& velocity);
	void VerticalCollisions(glm::vec2& velocity);
	void UpdateRaycastOrigins();

	//int m_handleNotify;
	Entity* m_platform;
	ICollider* m_cc;
	CollisionEngine * m_collision;
	//int m_collisionMaskDown;
	//int m_collisionMaskAny;
	int m_horizontalRayCount;
	int m_verticalRayCount;
	float m_horizontalRaySpacing;
	float m_verticalRaySpacing;
	float m_skinWidth;
	float m_maxClimbAngle;
	float m_maxDescendAngle;
    bool m_wasGnd;
};
