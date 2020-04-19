#pragma once

#include <monkey/activities/targetactivity.h>
#include <monkey/lua/luawrapper.h>
#include <string>

class SetState : public TargetActivity {
public:
    SetState (const std::string& state) : TargetActivity(), m_state(state) {}
    SetState (const LuaTable& );
    SetState (const ITable& );
    void Start() override;
    void Run (float dt) override {}
private:
    std::string m_state;
    pybind11::dict m_args;
};

