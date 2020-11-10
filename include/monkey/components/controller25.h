#pragma once

#include <monkey/components/icontroller.h>

class ICollider;
class ICollisionEngine;

struct RO {
    glm::vec2 topLeft, topRight;
    glm::vec2 bottomLeft, bottomRight;
};

class Controller25 : public IController {
public:
    Controller25(
        int maskWall,
        int horizontalRayCount = 4,
        int verticalRayCount = 4) : IController(), m_skinWidth(0.015f), m_horizontalRayCount(horizontalRayCount),
              m_verticalRayCount(verticalRayCount), m_maskWall(maskWall) {}
    Controller25(const ITable&);
    virtual ~Controller25();
    void CalculateRaySpacing();
    void UpdateRaycastOrigins();
    void Start() override;
    void Begin() override;
    void Move(glm::vec3&) override;
    bool grounded() const override;
    bool ceiling () const override;
	bool side () const override {return false;}
	void Update(double) override {}
    std::type_index GetType() override;
    void ResetShape(ICollider*);
    float getDepth() const;
    float getElevation() const;
    void setElevation(float);
private:
    float m_verticalRaySpacing;

    RO m_raycastOrigins;
    ICollider* m_collider;
    ICollisionEngine * m_collision;
    //int m_collisionMaskDown;
    //int m_collisionMaskAny;
    int m_horizontalRayCount;
    int m_verticalRayCount;
    float m_skinWidth;
    bool m_wasGnd;
    int m_maskWall;

    float m_depth;
    float m_elevation;
};


inline bool Controller25::ceiling () const {
    return false;
}

inline float Controller25::getDepth() const {
    return m_depth;
}

inline float Controller25::getElevation() const {
    return m_elevation;
}


inline void Controller25::setElevation(float elevation) {

    m_elevation = elevation;
}