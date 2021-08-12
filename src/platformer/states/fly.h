#pragma once

#include <monkey/states/platformerstate.h>

class Controller3D;
class Dynamics2D;

class Fly : public State {
public:
    Fly(const ITab&);
    void AttachStateMachine(StateMachine*) override;

    void Run(double) override;
    void Init (const ITab&) override;
    void End () override {}
private:
    Controller3D* m_controller;
    Dynamics2D * m_dynamics;
    IAnimator* m_animator;
    Entity * m_entity;

    std::string m_goingUpAnim;
    std::string m_goingDownAnim;
    std::string m_lieAnim;
    glm::vec2 m_initialVelocity;
    float m_timeOut;
    float m_targetVelocityX;
    int m_seq;
};

