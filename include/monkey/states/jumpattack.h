#pragma once

#include <monkey/states/platformerstate.h>

class JumpAttack : public PlatformerState {
public:
    JumpAttack (const ITab& t);
    //void AttachStateMachine(StateMachine * sm) override;

    void Init (pybind11::dict&) override;
    void Run(double) override;
    void End () override {}
    void ModifyAnimation() override {}
    void ResetAnimation() override {}
private:
    float m_speed;
    float m_accTimeAir;
    bool m_flipHorizontally;

    std::string m_anim;
};

