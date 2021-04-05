#pragma once

#include <monkey/components/statemachine.h>
#include <unordered_map>

class IAnimator;

class CharacterController : public Component {
public:
    CharacterController(const ITab&);
    void Start () override;
    void Update(double) override {}
    void turn (char);
    float getSpeed() const;
    char getDirection() const;
    using ParentClass = CharacterController;
    glm::vec4 getTextColor() const;
    glm::vec2 getTextOffset() const;
private:
    IAnimator* m_animator;
    char m_dir;
    float m_speed;
    glm::vec4 m_textColor;
    glm::vec2 m_textOffset;
};

inline glm::vec4 CharacterController::getTextColor() const {
    return m_textColor;
}

inline glm::vec2 CharacterController::getTextOffset() const {
    return m_textOffset;
}

inline float CharacterController::getSpeed() const {
    return m_speed;
}

inline char CharacterController::getDirection() const {
    return m_dir;
}

class StateCharacter : public StateMachine {
public:
    StateCharacter(float speed, char dir, const std::string& initialState);
    StateCharacter(const ITab& t);

    void SetDirection(char dir);
    char GetDirection() const;
    void Start () override;
    void Begin () override;
    float GetSpeed() const;
    std::type_index GetType() override;
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
    void Init (pybind11::dict&) override;
    void Run (double) override {}
    void End () override {}
    void AttachStateMachine(StateMachine*) override;
private:
    const StateCharacter* m_state;
    IAnimator* m_animator;
    std::string m_id;
};
