#pragma once

#include <gfx/activities/targetactivity.h>
#include <gfx/entity.h>

class Rotate : public TargetActivity {
public:
    Rotate(float degrees, float acceleration, float initialSpeed);
    void Start() override;
    void Run (float dt) override;
    void Reset() override {}
private:
    Entity* m_entity;
    float m_speed;
    float m_acceleration;
    float m_degreesCount;
    float m_degrees;
    std::string m_actorId;
};
