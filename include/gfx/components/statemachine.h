#pragma once

#include <string>
#include <gfx/component.h>
#include <memory>
#include <gfx/listener.h>
#include <gfx/transition.h>
#include <gfx/state.h>
#include <gfx/lua/luawrapper.h>
#include <gfx/hashpair.h>

class CollisionEngine;
class Renderer;

class StateMachine : public Component {
public:
    StateMachine(const std::string& initialState) : Component(), m_currentState{nullptr}, m_initialState(initialState) {}

    void AddState(const std::string&, std::shared_ptr<State>);
    void ChangeState(const std::string&);

    // impl component
    void Start() override;
    void Update(double) override ;
    State* GetCurrentState();

    using ParentClass = StateMachine;
protected:
    std::string m_initialState;
    std::unordered_map<std::string, std::shared_ptr<State>> m_states;
    State* m_currentState;
};

inline State* StateMachine::GetCurrentState() {
    return m_currentState;
}

class StateEvent {
public:
    virtual void Run(StateMachine*) = 0;
};

class SEChangeState : public StateEvent {
public:
    SEChangeState(const std::string& state) : m_nextState(state) {}
    void Run(StateMachine*) override;
private:
    std::string m_nextState;
};

class SECallback : public StateEvent {
public:
    SECallback (luabridge::LuaRef& ref) : m_ref(ref) {}
    void Run(StateMachine*) override;
private:
    luabridge::LuaRef m_ref;
};

struct KeyPress {
    int key;
    int action;
    std::string state;
    bool operator==(const KeyPress& other) const {
        return (key == other.key && action == other.action && state == other.state);
    }
};

namespace std {
    template<>
    struct hash<KeyPress>
    {
        std::size_t operator()(KeyPress const& s) const
        {
            std::size_t res = 0;
            hash_combine(res,s.state);
            hash_combine(res,s.key);
            hash_combine(res,s.action);
            return res;
        }
    };
}


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
    void AddKey(const std::string& currentState, int key, bool press, std::unique_ptr<StateEvent>);
    std::type_index GetType() override;
private:
    std::unordered_map<KeyPress, std::unique_ptr<StateEvent>> m_transitions;
};

// prob transition
class RandomTransitionStateMachine : public StateMachine {
public:
    RandomTransitionStateMachine(const std::string& initialState)
            : StateMachine(initialState) {}
    void Add(const std::string& initial, const std::string& next, float);
    void Update(double) override ;
    std::type_index GetType() override;
private:
    Transition m_transition;

};

inline void RandomTransitionStateMachine::Add(const std::string& initial, const std::string& next, float p) {
    m_transition.AddTransition(initial, next, p);
}

inline std::type_index KeyboardControlledStateMachine::GetType() {
    return std::type_index(typeid(StateMachine));
}

inline std::type_index RandomTransitionStateMachine::GetType() {
    return std::type_index(typeid(StateMachine));
}



