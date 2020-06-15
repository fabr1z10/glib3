#pragma once

#include <monkey/components/statemachine.h>
#include <functional>

class StateTransition : public StateAction {
public:
    StateTransition(const std::string& state);
    void Run (StateMachine*) override;
private:
    std::string m_state;
};



class StateFunc : public StateAction {
public:
    StateFunc(std::function<void()> f) : m_f(f) {}
    void Run (StateMachine*) override;
private:
    std::function<void()> m_f;

};