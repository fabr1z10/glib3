#pragma once

#include <gfx/component.h>
#include <memory>

class StateMachine2;

class State2 : public Ref {
public:
    virtual ~State2() = default;
    virtual void Init () = 0;
    virtual void Run (double) = 0;
    virtual void End () = 0;
    virtual std::shared_ptr<State2> clone() const = 0;
    virtual void AttachStateMachine(StateMachine2*) = 0;
    virtual bool KeyListener (int) {}
};

//!  A state machine.
/*!
 A state machine is a component that allows an entity to have a different
 behavior based on what the current state is. A state machine has a set of
 states, of which only one is active at any given time. It provides methods
 to get the current state, and change the state to a new one.
 */
class StateMachine2 : public Component {
public:
    StateMachine2(const std::string& initialState) : m_initialState(initialState), m_currentState(nullptr) {}
    StateMachine2(const StateMachine2&);
    void Start () override {}
    void Begin() override;
    void Update(double) override;
    void ResetState() ;
    std::string GetState() const;
    virtual void SetState (const std::string&);
    virtual void Refresh () {}
    void AddState(const std::string& id, std::shared_ptr<State2> state);
    std::shared_ptr<Component> clone() const override;
    using ParentClass = StateMachine2;
protected:
    State2* m_currentState;
    std::string m_currentStateId;
    std::string m_initialState;
    std::unordered_map<std::string, std::shared_ptr<State2>> m_states;
};

inline void StateMachine2::AddState(const std::string& id, std::shared_ptr<State2> state) {
    m_states.insert(std::make_pair(id, state));

}

inline std::string StateMachine2::GetState() const {
    return m_currentStateId;
}
