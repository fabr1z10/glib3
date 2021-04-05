#pragma once

#include <monkey/activities/targetactivity.h>
#include <monkey/entity.h>

class ScaleTo : public TargetActivity {
public:
    ScaleTo( float duration, float scale);
	ScaleTo(const ITab&);
    void Start() override;
    void Run (float dt) override;
private:
    // Entity* m_entity;
    //std::string m_id;
    float m_duration;
    float m_scale;
    float m_scaleSpeed;
    float m_currScale;
    float m_elapsedTime;
};
