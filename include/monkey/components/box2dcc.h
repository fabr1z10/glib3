#pragma once

#include <monkey/component.h>
#include <box2d/box2d.h>
#include "inputmethod.h"
#include "box2dcontrollerbase.h"


struct CRep {
    bool collide;
    float distance;
    b2Vec2 normal;
    float angle;

};

class Pippo : public b2RayCastCallback {
public:
    Pippo() : m_fraction(1.0f), n(0), collide(false) {}
    float ReportFixture(	b2Fixture* fixture, const b2Vec2& point,
                                    const b2Vec2& normal, float fraction) override;
    int n;
    bool collide;
    float m_fraction;
    b2Vec2 closestNormal;
};

class Box2DCharacterController : public Box2DCharacterControllerBase {
public:
    Box2DCharacterController(const ITab&);
    void Start() override;
    void Update(double) override;
    void checkGrounded();
    bool grounded() const;
    bool lgrounded() const;
    bool rgrounded() const;
private:
    CRep raycastDown(b2Vec2 P);
    CRep m_left;
    CRep m_right;
    std::unique_ptr<Pippo> m_callBack;
    float m_previousAngle;
};