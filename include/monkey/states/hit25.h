#pragma once

#include <monkey/components/statemachine.h>
#include <monkey/components/ianimator.h>

class Hit25 : public State {
public:
    Hit25 (const std::string& anim);
    Hit25 (const ITab& t);
    void AttachStateMachine(StateMachine * sm) override;
    void Init (const ITab&) override;
    void Run(double) override;
    void End () override {}
private:
    IAnimator* m_animator;
    std::string m_anim;
};

