#pragma once

#include <gfx/activities/targetactivity.h>
#include <gfx/components/inputmethod.h>
#include <gfx/entity.h>

class IAnimator;

class SetDemo : public TargetActivity {
public:
    SetDemo(bool value, bool sync, double length);
    void Start() override;
    void Run (float dt) override ;
    void addEvent(float t, int key, int type);
private:
    bool m_value;
    bool m_sync;
    double m_length;
    std::map<float, DemoKeyEvent> m_events;
    KeyboardInputMethod* m_im;
};

