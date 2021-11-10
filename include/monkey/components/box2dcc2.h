#pragma once

#include "box2dcontrollerbase.h"
#include "box2dlistener.h"


class Box2DCharacterController2 : public Box2DCharacterControllerBase, public IBox2DBodyListener {
public:
    Box2DCharacterController2(const ITab&);
    void Start() override;
    void Update(double) override;
    void startContact(Box2DBody* other, b2Contact*, bool) override;
    void endContact(Box2DBody* other, b2Contact*, bool) override;
private:
    void applyFriction(double);
    void applyGravity(double);
    float m_maxSpeed;
    float m_acceleration;
    float m_friction;
    float m_xVel;
    float m_yVel;
    float m_gravity;
};