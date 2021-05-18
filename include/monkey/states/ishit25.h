#pragma once

#include <monkey/components/statemachine.h>
#include <monkey/components/depth25.h>
#include <glm/glm.hpp>

class Entity;
class IAnimator;
class IController;
class ICollisionEngine;
class Dynamics2D;
class Controller25;


class IsHit25 : public State {
public:
    //FoeWalk25(float speed, float acceleration, bool fliph);

    IsHit25(const ITab &);

    void Run(double) override;

    void Init(const ITab&) override;

    void End() override;

    void AttachStateMachine(StateMachine *) override;

protected:
    float m_distanceTravelled;
    Controller25 *m_controller;
    IAnimator *m_animator;
    Entity *m_entity;
    Entity *m_player;
    Controller25* m_pc;
    Dynamics2D *m_dynamics;
    float m_acceleration;
    float m_sgn;
    std::string m_anim;
    ICollisionEngine *m_collision;

};

