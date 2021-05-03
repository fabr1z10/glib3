#pragma once

#include <monkey/components/icontroller.h>
#include <glm/glm.hpp>

class ICollisionEngine;
class ICollider;
class PlatformComponent;

struct CollisionDetails3D {
    bool above, below;
    bool left, right;

    bool climbingSlope;
    bool descendingSlope;

    float slopeAngle, slopeAngleOld;
    void Reset();
};

inline void CollisionDetails3D::Reset() {
    above = below = false;
    left = right = false;

    climbingSlope = false;
    descendingSlope = false;
    slopeAngleOld = slopeAngle;
    slopeAngle = 0.0f;
}

struct RaycastOrigins3D {
	float left, right;
	float bottom, top;
	float front, back;
};


class Controller3D : public IController {
public:
    Controller3D(float maxClimbAngle, float maxDescendAngle, float skinwidth = .015f, int horizontalRayCount = 4, int verticalRayCount = 4)
            : IController(), m_maxClimbAngle(maxClimbAngle), m_maxDescendAngle(maxDescendAngle), m_skinWidth(skinwidth), m_horizontalRayCount(horizontalRayCount), m_verticalRayCount(verticalRayCount), m_platform(nullptr) {}
    virtual ~Controller3D() {}

    Controller3D (const ITab&);
    void Start() override;
    void Begin() override;
    bool IsFalling(int x, int z);
    void Move(glm::vec3&) override;
    bool grounded() const override;
    bool ceiling () const override;
	bool side () const override {return false;}


    void CalculateRaySpacing();
    void Update(double) override {}
//    void ResetShape(ICollider*);
//    //void ForceMove(glm::vec2&);
    CollisionDetails3D m_details;
    RaycastOrigins3D m_raycastOrigins;
//    using ParentClass = Controller3D;
//    void DetachFromPlatform();
//    void ForceDetach() { m_platform = nullptr; }
    std::type_index GetType() override;
	void ClimbSlope(glm::vec3&, float);

    //RayCastHit2D Raycast(glm::vec2 origin, glm::vec2 direction, float length, int mask);
private:
    //std::vector<Collider*> m_ppp;
    void HorizontalCollisions(glm::vec3& velocity);
    void VerticalCollisions(glm::vec3& velocity);
    void UpdateRaycastOrigins();
	ICollisionEngine * m_collision;
	int m_maskUp;
	int m_maskDown;

	glm::vec3 m_halfSize;
	glm::vec3 m_shift;
//    //int m_handleNotify;
    Entity* m_platform;
    ICollider* m_cc;
    ICollisionEngine * m_engine;
//    //int m_collisionMaskDown;
//    //int m_collisionMaskAny;
    int m_horizontalRayCount;
    int m_verticalRayCount;
    float m_horizontalRaySpacing;
    float m_verticalRaySpacing;
    float m_skinWidth;
    float m_maxClimbAngle;
    float m_maxDescendAngle;
    bool m_wasGnd;
    CollisionDetails3D m_detailsOld;
    float m_widthX;
    float m_widthZ;
    float m_horXSpacing;
    float m_horZSpacing;
	bool m_debug;

};

inline std::type_index Controller3D::GetType() {
    return std::type_index(typeid(IController));
}

inline bool Controller3D::grounded() const {
    return m_details.below;
}

inline bool Controller3D::ceiling () const {
    return m_details.above;
}