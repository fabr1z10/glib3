#pragma once

#include <gfx/activities/targetactivity.h>
#include <string>

class SetState : public TargetActivity {
public:
    SetState (const std::string& state) : TargetActivity(), m_state(state) {}
    void Start() override;
    void Run (float dt) override {}
private:
    std::string m_state;

};
