#pragma once

#include <monkey/components/statemachine.h>

class Controller2D;
class IController;
class Dynamics2D;
class InputMethod;
class AnimationRenderer;

class __attribute__ ((visibility ("default"))) PlatformerState : public State {
public:
    PlatformerState();
    PlatformerState(const PlatformerState&);
    PlatformerState(const ITab&);
    void AttachStateMachine(StateMachine*) override;
    //bool KeyListener (int) override;
    void SetOverrideAnimation(const std::string& anim);
    void UpdateAnimation();
    virtual void ModifyAnimation() = 0;
    virtual void ResetAnimation() = 0;
protected:
    AnimationRenderer* m_animator;
    IController * m_controller;
    Dynamics2D * m_dynamics;
    InputMethod * m_input;
    Entity * m_entity;
    std::string m_overrideAnimation;
};