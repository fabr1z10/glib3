#pragma once

#include <monkey/components/statemachine.h>
#include <monkey/components/ianimator.h>

class Hit25 : public State {
public:
    Hit25 (const std::string& anim);
    Hit25 (const Hit25& orig);
    Hit25 (const ITable& t);
    void AttachStateMachine(StateMachine * sm) override;
    void Init (pybind11::dict&) override;
    void Run(double) override;
    void End () override {}
    std::shared_ptr<State> clone() const override;
private:
    IAnimator* m_animator;
    std::string m_anim;
};

