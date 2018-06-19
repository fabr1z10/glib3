#pragma once

#include <gfx/activity.h>
#include <gfx/entity.h>

class DelayTime : public Activity {
public:
    DelayTime(int activityId, float sec) : Activity(activityId), m_time{sec}, m_elapsed{0.0f} {}
    void Start() override ;
    void Run (float dt) override;
private:
    float m_time;
    float m_elapsed;
};