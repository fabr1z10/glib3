#pragma once

#include <box2d/box2d.h>
#include <monkey/component.h>


class Box2DBody;

class Box2DListener : public b2ContactListener {
public:
    void BeginContact(b2Contact* contact) override;

    void EndContact(b2Contact* contact) override;
};


class IBox2DBodyListener {
public:
    IBox2DBodyListener() = default;
    virtual void startContact(Box2DBody* other, b2Contact*, bool) = 0;
    virtual void endContact(Box2DBody* other, b2Contact*, bool) = 0;
};

//class Box2DPlatfomerListener : public IBox2DBodyListener {
//public:
//    Box2DPlatfomerListener(const ITab& t) : IBox2DBodyListener(t) {}
//    void startContact(Box2DBody* other, b2Contact*, bool) override;
//    void endContact(Box2DBody* other, b2Contact*, bool) override {}
//};