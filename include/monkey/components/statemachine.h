#pragma once

#include <monkey/component.h>
#include <monkey/lua/luawrapper.h>
#include <memory>

class StateMachine;

class StateAction {
public:
    virtual void Run (StateMachine*) = 0;
};


class State : public Ref {
public:
    virtual ~State() = default;
    // init is called every time this state is set, so DON't put initialization code here!
    virtual void Init () = 0;
    // init with data
    virtual void Init (luabridge::LuaRef);
    virtual void Run (double) = 0;
    virtual void End () = 0;
    virtual std::shared_ptr<State> clone() const = 0;
    // This is called only once when the statemachine begins, so PUT your initialization code here!
    virtual void AttachStateMachine(StateMachine*);
    virtual bool KeyListener (int);
    void AddKey (int, std::shared_ptr<StateAction>);
protected:
    StateMachine* m_sm;
    std::unordered_map<int, std::shared_ptr<StateAction>> m_actions;
};



//!  A state machine.
/*!
 A state machine is a component that allows an entity to have a different
 behavior based on what the current state is. A state machine has a set of
 states, of which only one is active at any given time. It provides methods
 to get the current state, and change the state to a new one.
 */
class StateMachine : public Component {
public:
    StateMachine() : m_currentState(nullptr), Component() {}
    StateMachine(const std::string& initialState) : m_initialState(initialState), m_currentState(nullptr) {}
    StateMachine(const StateMachine&);
    void Start () override {}
    void Begin() override;
    void Update(double) override;
    void ResetState() ;
    std::string GetState() const;
    virtual void SetState (const std::string&);
    void SetState (const std::string&, luabridge::LuaRef);

    State* GetState (const std::string&);
    virtual void Refresh () {}
    void AddState(const std::string& id, std::shared_ptr<State> state);
    std::shared_ptr<Component> clone() const override;
    using ParentClass = StateMachine;
protected:
    State* m_currentState;
    std::string m_currentStateId;
    std::string m_initialState;
    std::unordered_map<std::string, std::shared_ptr<State>> m_states;
};

inline void StateMachine::AddState(const std::string& id, std::shared_ptr<State> state) {
    m_states.insert(std::make_pair(id, state));

}

inline std::string StateMachine::GetState() const {
    return m_currentStateId;
}


