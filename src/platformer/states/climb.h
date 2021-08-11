#pragma once

#include <monkey/states/platformerstate.h>
#include "../walkanim.h"

class Controller3D;
class Dynamics2D;
class InputMethod;

// this is the walk state for moving in 3d world (x, z horizontal)
class Climb : public State {
public:
    /**
     *
     * @param speed The maximum speed
     * @param acceleration The acceleration
     * @param fliph Flip entity horizontally when going left
     */
    Climb(const ITab&);
    void AttachStateMachine(StateMachine*) override;

    void Run(double) override;
    void Init (const ITab&) override;
    void End () override;


private:
    Controller3D* m_controller;
    Dynamics2D * m_dynamics;
    InputMethod * m_input;
    IAnimator* m_animator;
    Entity * m_entity;

    bool m_xMoveAllowed;
    bool m_flipHorizontally;
    float m_speed;
    float m_acceleration;
    float m_velocitySmoothing;
    float m_jumpSpeed;
    std::string m_climbAnim;
    std::string m_idleAnim;
    glm::vec3 m_yMin_goto;
    glm::vec3 m_yMax_goto;
    float m_yMin;
    float m_yMax;
};

