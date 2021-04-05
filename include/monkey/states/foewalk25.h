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


class FoeWalk25 : public State {
public:
    //FoeWalk25(float speed, float acceleration, bool fliph);

    FoeWalk25(const ITab &);

    void Run(double) override;

    void Init(pybind11::dict &) override;

    void End() override;

    void AttachStateMachine(StateMachine *) override;
    void computeDirection();
protected:
    Controller25 *m_controller;
    IAnimator *m_animator;
    Entity *m_entity;
    Entity *m_target;
    Controller25* m_pc;
    Dynamics2D *m_dynamics;
    StateMachine* m_targetSM;
    bool m_flipHorizontal;
    float m_speed;
    bool m_jumping;
    float m_acceleration;
    float m_attackPos;
    //float m_sdelta;
    float m_probAttack;
    float m_targetVelocityX;
    float m_targetVelocityY;
    bool m_inRange;
    bool m_jumpAttack;

    ICollisionEngine *m_collision;
    std::vector<std::string> m_attacks;
    size_t m_attackCount;
};
