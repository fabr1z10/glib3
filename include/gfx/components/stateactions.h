#pragma once

#include <gfx/components/statemachine.h>
#include <gfx/lua/luawrapper.h>
#include <functional>

class StateTransition : public StateAction {
public:
    StateTransition(const std::string& state);
    void Run (StateMachine*) override;
private:
    std::string m_state;
};

class StateCallback : public StateAction {
public:
    StateCallback(luabridge::LuaRef f);
    void Run (StateMachine*) override;
private:
    luabridge::LuaRef m_f;

};

class StateFunc : public StateAction {
public:
    StateFunc(std::function<void()> f) : m_f(f) {}
    void Run (StateMachine*) override;
private:
    std::function<void()> m_f;

};