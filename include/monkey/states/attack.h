#pragma once

#include <monkey/components/statemachine.h>
#include <monkey/components/ianimator.h>

class Attack : public State {
public:
    Attack (const Attack& orig);
    Attack (const ITable& t);
    std::shared_ptr<State> clone() const override;

    void AttachStateMachine(StateMachine * sm) override;

    void Init (pybind11::dict&) override;
    void Run(double) override;
    void End () override {}
private:
    IAnimator* m_animator;
    std::string m_anim;
};

