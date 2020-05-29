#pragma once

#include <monkey/components/statemachine.h>
#include <monkey/components/depth25.h>
#include <glm/glm.hpp>

class InputMethod;
class Entity;
class IAnimator;
class IController;
class ICollisionEngine;
class Dynamics2D;


class Walk25 : public State {
public:
    Walk25(float speed, float acceleration, bool fliph, bool anim4, float jumpspeed, char dir='e');
    Walk25(const Walk25&);
    Walk25 (const ITable&);
    std::shared_ptr<State> clone() const override;
    void Run(double) override;
    void Init (pybind11::dict&) override;
    void End () override;
    float GetSpeed() const;
    void AttachStateMachine(StateMachine*) override;
    bool flipHorizontally() const;
    bool isFourWay() const;
    //void AddKey (int, std::shared_ptr<StateAction>);
    //bool KeyListener (int) override;
    //virtual void ModifyAnimation() = 0;
    // virtual void ResetAnimation() = 0;
protected:
    InputMethod * m_input;
    IController* m_controller;
    IAnimator* m_animator;
    Entity * m_entity;
    Dynamics2D * m_dynamics;

    bool m_flipHorizontal;
    bool m_4WayAnim;
    float m_speed;
    float m_velocitySmoothingX;
    float m_velocitySmoothingY;
    float m_acceleration;
    float m_jumpVelocity;
    ICollisionEngine * m_collision;
    char m_dir;
    Depth25* m_depth;
    bool m_airAttack;
    std::string m_currentAttack;
    std::unordered_map<int, std::string> m_attacks;
};

inline bool Walk25::flipHorizontally() const {
    return m_flipHorizontal;
}
inline bool Walk25::isFourWay() const {
    return m_4WayAnim;
}
inline float Walk25::GetSpeed() const {

    return m_speed;
}