#pragma once

#include <gfx/components/statemachine2.h>
#include <unordered_map>

class Animator;



class StateCharacter : public StateMachine2 {
public:
    StateCharacter(char dir, const std::string& initialState);
    void SetDirection(char dir);
    char GetDirection() const;
    void Start () override;
    void Begin () override;
    std::type_index GetType() override;
private:
    char m_dir;
};


inline std::type_index StateCharacter::GetType() {
    return std::type_index(typeid(StateMachine2));
}


inline char StateCharacter::GetDirection() const {
    return m_dir;
}

class AnimateCharState : public State2 {
public:
    AnimateCharState(const StateCharacter* state, Animator* animator, const std::string& id) :
            m_state(state), m_id(id), m_animator(animator) {}
    virtual void Init () override;
    virtual void Run (double) override {}
    virtual void End () override {}
private:
    const StateCharacter* m_state;
    Animator* m_animator;
    std::string m_id;
};