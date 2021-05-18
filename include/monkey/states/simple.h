#pragma once

#include <monkey/components/statemachine.h>
#include <glm/glm.hpp>

class IAnimator;

class NullState : public State {
public:
    NullState ();
    NullState (const ITab&);
    void Run(double) override;
    void Init (const ITab&) override;
    void End () override;
};

class SimpleState : public State {
public:
    SimpleState(const std::string& anim);
    SimpleState(const ITab&);
    void Run(double) override;
    void Init (const ITab&) override;
    void End () override;
    void AttachStateMachine(StateMachine*) override;
protected:
    bool m_endOnAnimComplete;
    std::string m_nextState;
    std::string m_anim;
    IAnimator* m_animator;
    Entity * m_entity;
};