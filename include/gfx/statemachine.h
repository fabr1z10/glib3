#pragma once

#include <string>
#include <gfx/component.h>
#include <memory>
#include <gfx/listener.h>

class CollisionEngine;
class Renderer;
class Entity;

class State {
public:
    State() : m_nextState() {}
    virtual void End () = 0;
    // returns true if state changes
    virtual bool Run (double) = 0;
    virtual void Start () = 0;
    // called once!!!
    virtual void Init() = 0;
    std::string GetNextState() const;
    std::string GetId() const;
protected:
    std::string m_id;
    std::string m_nextState;
    Entity* m_entity;
};

inline std::string State::GetNextState() const {
    return m_nextState;
}

inline std::string State::GetId() const {
    return m_id;
}


class StateMachine : public Component {
public:
    StateMachine(const std::string& initialState) : Component(), m_initialState(initialState) {}

    void AddState(const std::string&, std::shared_ptr<State>);
    void ChangeState(const std::string&);

    // impl component
    void Start() override;
    void Update(double) override ;

    using ParentClass = StateMachine;
protected:
    std::string m_initialState;
    std::unordered_map<std::string, std::shared_ptr<State>> m_states;
    State* m_currentState;
};


class KeyboardControlledStateMachine : public StateMachine, public KeyboardListener {
public:
    KeyboardControlledStateMachine(const std::string& initialState)
            : StateMachine(initialState) {}

    // listener
    void KeyCallback(GLFWwindow *, int, int, int, int) override;
    void Enable(bool) override {}
    // enable specific keys
    void EnableKey(int, bool) override {}
private:
    std::unordered_map<std::string, std::unordered_map<int, std::string>> m_transitions;
};



