#pragma once

#include <monkey/activities/targetactivity.h>
#include <monkey/lua/luawrapper.h>
#include <string>

class SetState : public TargetActivity {
public:
    SetState (const std::string& state) : TargetActivity(), m_state(state) {}
    void Start() override;
    void Run (float dt) override {}
private:
    std::string m_state;
};

class SetStateWithArgs : public TargetActivity {
public:
    SetStateWithArgs (const std::string& state, luabridge::LuaRef args) : TargetActivity(), m_state(state), m_args(args) {}
    void Start() override;
    void Run (float dt) override {}
private:
    luabridge::LuaRef m_args;
    std::string m_state;

};
