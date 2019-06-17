#pragma once


#include <gfx/components/statemachine.h>

class Controller2D;
class Dynamics2D;
class InputMethod;
class Animator;

class PlatformerState : public State {
public:
    PlatformerState();
    PlatformerState(const PlatformerState&);
    void AttachStateMachine(StateMachine*) override;
    void AddKey (int, std::shared_ptr<StateAction>);
    bool KeyListener (int) override;
protected:
    Animator* m_animator;
    StateMachine* m_sm;
    Controller2D * m_controller;
    Dynamics2D * m_dynamics;
    InputMethod * m_input;
    Entity * m_entity;
    std::unordered_map<int, std::shared_ptr<StateAction>> m_actions;
};