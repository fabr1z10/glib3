#pragma once

#include <gfx/component.h>
#include <memory>

class State2 {
public:
    virtual ~State2() = default;
    virtual void Init () = 0;
    virtual void Run (double) = 0;
    virtual void End () = 0;
};


class StateMachine2 : public Component {
public:
    StateMachine2();
    void Start () override;
    void Update(double) override;
    void ResetState() ;
    void SetState (const std::string&);
private:
    State2* m_currentState;
    std::string m_currentStateId;
    std::string m_initialState;
    std::unordered_map<std::string, std::unique_ptr<State2>> m_states;
};
