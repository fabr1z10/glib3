#pragma once

#include <monkey/activities/targetactivity.h>
#include <monkey/entity.h>

class Renderer;

class Blink : public TargetActivity {
public:
    //! \name Constructors
    //@{
    /*! Blink the given actor for a certain time, each blink lasting t.
     */
    Blink(float totalDuration, float blinkDuration);
    Blink (const ITable&);
    //@}
    void Start() override;
    void Run (float dt) override ;
    virtual void SetComplete();

private:
    float m_timer;
    float m_timer2;
    bool m_visible;
    float m_duration;
    float m_blinkDuration;
    Renderer* m_renderer;
    std::string m_actorId;
};

