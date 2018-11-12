#pragma once

#include <gfx/activity.h>
#include <gfx/entity.h>

class ScaleTo : public Activity {
public:
    ScaleTo(const std::string& id, float duration, float scale);
    void Start() override;
    void Run (float dt) override;
private:
    Entity* m_entity;
    std::string m_id;
    float m_duration;
    float m_scale;
    float m_scaleSpeed;
    float m_currScale;
    float m_elapsedTime;
};
