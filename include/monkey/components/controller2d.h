#pragma once

#include <monkey/components/icontroller.h>
#include <glm/glm.hpp>


class ICollisionEngine;
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


class Controller2D : public IController {
public:
	Controller2D(
			float maxClimbAngle,
			float maxDescendAngle,
			int maskUp,
			int maskDown,
			float skinwidth = .015f,
			int horizontalRayCount = 4,
			int verticalRayCount = 4)
		: IController(), m_maxClimbAngle(maxClimbAngle), m_maxDescendAngle(maxDescendAngle), m_skinWidth(skinwidth), m_horizontalRayCount(horizontalRayCount),
		  m_verticalRayCount(verticalRayCount), m_maskUp(maskUp), m_maskDown(maskDown), m_platform(nullptr) {}
    Controller2D(const ITab&);
	virtual ~Controller2D();
	void Start() override;
	void Begin() override;
	bool IsFalling(int);
    void setMask(int maskUp, int maskDown);
	void Move(glm::vec3&) override;
    bool grounded() const override;
    bool ceiling () const override;
	bool side () const override;
	void ClimbSlope(glm::vec2&, float);
	void DescendSlope(glm::vec2&);
	//void CalculateRaySpacing();
	void Update(double) override {}
	//void ForceMove(glm::vec2&);
	CollisionDetails m_details;

	using ParentClass = Controller2D;
	void DetachFromPlatform();
	void ForceDetach() { m_platform = nullptr; }
    std::type_index GetType() override;
	void updateRaycastOrigins();

    //RayCastHit2D Raycast(glm::vec2 origin, glm::vec2 direction, float length, int mask);
private:
	RaycastOrigins m_raycastOrigins;
	//std::vector<Collider*> m_ppp;
	void HorizontalCollisions(glm::vec2& velocity);
	void VerticalCollisions(glm::vec2& velocity);


	glm::vec2 m_halfSize;
	glm::vec2 m_shift;
	//int m_handleNotify;
	Entity* m_platform;
	//ICollider* m_cc;
	ICollisionEngine * m_collision;
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
	int m_maskUp;
	int m_maskDown;
	bool m_debug;
};

inline std::type_index Controller2D::GetType() {
    return std::type_index(typeid(IController));
}

inline bool Controller2D::grounded() const {
    return m_details.below;
}

inline bool Controller2D::ceiling () const {
return m_details.above;
}

inline bool Controller2D::side() const {
	return m_details.left || m_details.right;
}