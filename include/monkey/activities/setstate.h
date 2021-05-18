#pragma once

#include <monkey/activities/targetactivity.h>
#include <string>

class SetState : public TargetActivity {
public:
    SetState (const std::string& state) : TargetActivity(), m_state(state) {}
    SetState (const ITab& );
    void Start() override;
    void Run (float dt) override {}
private:
    std::string m_state;
    std::unique_ptr<ITab> m_args;
};

