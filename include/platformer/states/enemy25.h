#pragma once

#include <gfx/components/statemachine.h>
#include <gfx/components/depth25.h>
#include <glm/glm.hpp>

class InputMethod;
class Entity;
class IAnimator;
class ICollisionEngine;

class EnemyWalk25 : public State {
public:
    EnemyWalk25(float reach, float speed, float acceleration, bool fliph, char dir='e');
    EnemyWalk25(const EnemyWalk25&);
    std::shared_ptr<State> clone() const override;
    void Run(double) override;
    void Init () override;
    void End () override;
    float GetSpeed() const;
    void AttachStateMachine(StateMachine*) override;
    bool flipHorizontally() const;
    bool isFourWay() const;
protected:
    InputMethod * m_input;
    IAnimator* m_animator;
    Entity * m_entity;
    bool m_flipHorizontal;
    bool m_4WayAnim;
    float m_speed;
    bool m_idle;
    float m_lengthToDo;
    float m_lengthCount;
    //glm::vec2 m_velocity;
    float m_velocitySmoothingX;
    float m_velocitySmoothingY;
    float m_acceleration;
    glm::vec3 m_targetPosition;
    float m_jumpVelocity;
    ICollisionEngine * m_collision;
    char m_dir;
    Depth25* m_depth;
    Entity* m_target;
    glm::vec2 m_targetVelocity;
    float m_reach;

};

inline bool EnemyWalk25::flipHorizontally() const {
    return m_flipHorizontal;
}
inline bool EnemyWalk25::isFourWay() const {
    return m_4WayAnim;
}
inline float EnemyWalk25::GetSpeed() const {

    return m_speed;
}