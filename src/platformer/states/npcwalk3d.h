#pragma once

#include <monkey/components/statemachine.h>
#include "../walkanim.h"

class Controller3D;
class Dynamics2D;

// this is the walk state for moving in 3d world (x, z horizontal)
class NPCWalk3D : public State {
public:
    /**
     *
     * @param speed The maximum speed
     * @param acceleration The acceleration
     * @param fliph Flip entity horizontally when going left
     */
    NPCWalk3D(const ITab&);
    void AttachStateMachine(StateMachine*) override;

    void Run(double) override;
    void Init (const ITab&) override;
    void End () override;


private:
    Controller3D* m_controller;
    Dynamics2D * m_dynamics;
    IAnimator* m_animator;
    Entity * m_entity;

    bool m_flipHorizontally;
    float m_speed;
    float m_acceleration;
    float m_velocitySmoothing;
    float m_jumpSpeed;
    std::string m_walkAnim;
    std::string m_jumpState;
    std::string m_idleAnim;
    std::shared_ptr<WalkAnim> m_walkAnimator;
    std::vector<glm::vec2> m_path;
    int m_currentSegment;
    bool m_loop;
    glm::vec2 m_targetVelocity;
};

