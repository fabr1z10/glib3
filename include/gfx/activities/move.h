#pragma once

#include <gfx/activity.h>
#include <gfx/entity.h>

class MoveTo : public Activity {
public:
    MoveTo(Entity* entity, glm::vec2 pos, float speed, bool relative, bool immediate);
    MoveTo(const std::string& actorId, glm::vec2 pos, float speed, bool relative, bool immediate);
    void Start() override;
    void Run (float dt) override;
    void Reset() override;
    void SetAcceleration(float acceleration);
protected:
    Entity* m_entity;
    glm::vec2 m_toPos;
    glm::vec2 m_velocity;
    glm::vec2 m_finalPosition;
    glm::vec2 m_accelerationVector;
    float m_speed;
    float m_lengthToCover;
    float m_lengthCovered;
    float m_acceleration;
    bool m_relative;
    bool m_immediate;
    std::string m_actorId;
};

inline void MoveTo::SetAcceleration(float acceleration) {
    m_acceleration = acceleration;
}

class MoveAndRotateTo : public MoveTo {
public:
    MoveAndRotateTo (const std::string& actorId, glm::vec2 pos, float speed, bool relative, bool immediate, float angle, bool angleRelative);
    void Start() override;
    void Run (float dt) override;
private:
    float m_deltaAngle;
    bool m_angleRelative;
    float m_initAngle;
    float m_endAngle;
    float m_angle;
};

class MoveGravity : public Activity {
public:
    MoveGravity(const std::string &actorId, glm::vec2 initialVelocity, float g, float yStop, float rotationSpeed, float finalRotation);

    void Start() override;

    void Run(float dt) override;

private:
    Entity *m_entity;
    float m_yStop;
    glm::vec2 m_initialVelocity;
    glm::vec2 m_velocity;
    float m_g;
    std::string m_actorId;
    float m_angle;
    float m_rotationSpeed;
    float m_finalRotation;
};