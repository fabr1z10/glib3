#pragma once

#include <monkey/components/statemachine.h>
#include <unordered_map>

class IAnimator;

class StateCharacter : public StateMachine {
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
    return std::type_index(typeid(StateMachine));
}


inline char StateCharacter::GetDirection() const {
    return m_dir;
}

inline float StateCharacter::GetSpeed() const {
    return m_speed;
}

class AnimateCharState : public State {
public:
    AnimateCharState(const std::string& id) : m_id(id) {}
    void Init () override;
    void Run (double) override {}
    void End () override {}
    void AttachStateMachine(StateMachine*) override;
    std::shared_ptr<State> clone() const override;
private:
    const StateCharacter* m_state;
    IAnimator* m_animator;
    std::string m_id;
};
