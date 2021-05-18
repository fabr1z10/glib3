#pragma once

#include <monkey/components/statemachine.h>
#include <monkey/components/ianimator.h>

class Attack : public State {
public:
    Attack (const ITab& t);

    void AttachStateMachine(StateMachine * sm) override;

    void Init (const ITab&) override;
    void Run(double) override;
    void End () override {}
private:
    IAnimator* m_animator;
    std::string m_anim;
};

