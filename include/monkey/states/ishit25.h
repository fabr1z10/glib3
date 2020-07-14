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

    IsHit25(const IsHit25 &);

    IsHit25(const ITable &);

    std::shared_ptr<State> clone() const override;

    void Run(double) override;

    void Init(pybind11::dict &) override;

    void End() override;

    void AttachStateMachine(StateMachine *) override;

protected:
    Controller25 *m_controller;
    IAnimator *m_animator;
    Entity *m_entity;
    Entity *m_player;
    Controller25* m_pc;
    Dynamics2D *m_dynamics;
    float m_acceleration;
    std::string m_anim;
    ICollisionEngine *m_collision;

};
