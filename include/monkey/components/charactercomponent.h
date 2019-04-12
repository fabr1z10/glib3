#pragma once

#include <gfx/components/statemachine2.h>
#include <unordered_map>

class Animator;

class StateCharacter : public StateMachine2 {
public:
    StateCharacter(float speed, char dir, const std::string& initialState);
    StateCharacter(const StateCharacter&);
    void SetDirection(char dir);
    char GetDirection() const;
    void Start () override;
    void Begin () override;
    float GetSpeed() const;
    std::type_index GetType() override;
    std::shared_ptr<Component> clone() const override;
private:
    float m_speed;
    char m_dir;
};


inline std::type_index StateCharacter::GetType() {
    return std::type_index(typeid(StateMachine2));
}


inline char StateCharacter::GetDirection() const {
    return m_dir;
}

inline float StateCharacter::GetSpeed() const {
    return m_speed;
}

class AnimateCharState : public State2 {
public:
    AnimateCharState(const std::string& id) : m_id(id) {}
    void Init () override;
    void Run (double) override {}
    void End () override {}
    void AttachStateMachine(StateMachine2*) override;
    std::shared_ptr<State2> clone() const override;
private:
    const StateCharacter* m_state;
    Animator* m_animator;
    std::string m_id;
};
