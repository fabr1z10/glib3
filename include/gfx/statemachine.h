#pragma once

#include <string>
#include <gfx/component.h>
#include <memory>
#include <gfx/listener.h>
#include <gfx/transition.h>

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
    virtual void Init(Entity*);
    std::string GetNextState() const;
    std::string GetId() const;
    void SetId(const std::string& id);
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


inline void State::SetId(const std::string& id) {
    m_id = id;
}

// do  nothing sttae
class EmptyState : public State {
public:
    void End () override {}
    // returns true if state changes
    bool Run (double) override { return false; }
    void Start () override {}
};

class StateMachine : public Component {
public:
    StateMachine(const std::string& initialState) : Component(), m_currentState{nullptr}, m_initialState(initialState) {}

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


// Transition controlled via keyboard
class KeyboardControlledStateMachine : public StateMachine, public KeyboardListener {
public:
    KeyboardControlledStateMachine(const std::string& initialState)
            : StateMachine(initialState) {}

    // listener
    void KeyCallback(GLFWwindow *, int, int, int, int) override;
    void Enable(bool) override {}
    // enable specific keys
    void EnableKey(int, bool) override {}
    void AddKey(const std::string& currentState, int key, const std::string& nextState);
private:
    std::unordered_map<std::string, std::unordered_map<int, std::string>> m_transitions;
};

// prob transition
class RandomTransitionStateMachine : public StateMachine {
public:
    RandomTransitionStateMachine(const std::string& initialState)
            : StateMachine(initialState) {}
    void Add(const std::string& initial, const std::string& next, float);
    void Update(double) override ;
private:
    Transition m_transition;

};

inline void RandomTransitionStateMachine::Add(const std::string& initial, const std::string& next, float p) {
    m_transition.AddTransition(initial, next, p);
}





