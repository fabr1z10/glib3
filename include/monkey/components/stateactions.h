#pragma once

#include <monkey/components/statemachine.h>
#include <functional>

class StateTransition : public StateAction {
public:
    StateTransition(const std::string& state);
    StateTransition(const ITab&);

    void Run (StateMachine*) override;
private:
    std::string m_state;
};



class StateFunc : public StateAction {
public:
    StateFunc(const ITab& t);
    void Run (StateMachine*) override;
private:

    pybind11::function m_callback;
};