#pragma once

#include <gfx/activities/targetactivity.h>
#include <gfx/entity.h>

class Renderer;

class Blink : public TargetActivity {
public:
    //! \name Constructors
    //@{
    /*! Blink the given actor for a certain time, each blink lasting t.
     */
    Blink(float totalDuration, float blinkDuration);
    //@}
    void Start() override;
    void Run (float dt) override ;
private:
    float m_timer;
    float m_timer2;
    bool m_visible;
    float m_duration;
    float m_blinkDuration;
    Renderer* m_renderer;
    std::string m_actorId;
};

