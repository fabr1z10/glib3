#pragma once

#include <monkey/runner.h>
#include <box2d/box2d.h>

class Box2DWorld : public Runner {
public:
    Box2DWorld(const ITab& t);
    void Update(double) override;
    float getScalingFactor() const;
    b2Body* createBody(b2BodyDef*);
private:
    std::unique_ptr<b2World> m_world;
    float m_scalingFactor;
    int32 m_velocityIterations;
    int32 m_positionIterations;
};

inline float Box2DWorld::getScalingFactor() const {
    return m_scalingFactor;
}

