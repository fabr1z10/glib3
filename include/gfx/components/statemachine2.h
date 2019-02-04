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
    StateMachine2(const std::string& initialState) : m_initialState(initialState), m_currentState(nullptr) {}
    void Start () override {}
    void Begin() override;
    void Update(double) override;
    void ResetState() ;
    void SetState (const std::string&);
    void AddState(const std::string& id, std::unique_ptr<State2> state);
private:
    State2* m_currentState;
    std::string m_currentStateId;
    std::string m_initialState;
    std::unordered_map<std::string, std::unique_ptr<State2>> m_states;
};

inline void StateMachine2::AddState(const std::string& id, std::unique_ptr<State2> state) {
    m_states.insert(std::make_pair(id, std::move(state)));
}

