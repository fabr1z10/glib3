#pragma once

#include <gfx/activities/targetactivity.h>
#include <gfx/entity.h>

class MoveTo : public TargetActivity {
public:
    MoveTo(glm::vec2 pos, float speed, bool relative, bool immediate);
    MoveTo(int id, glm::vec2 pos, float speed, bool relative, bool immediate) : MoveTo(pos, speed, relative, immediate) {
        SetId(id);
    }
    MoveTo(const std::string& tag, glm::vec2 pos, float speed, bool relative, bool immediate) : MoveTo(pos, speed, relative, immediate) {
        SetTag(tag);
    }
    void Start() override;
    void Run (float dt) override;
    void Reset() override;
    void SetAcceleration(float acceleration);
protected:
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
};

inline void MoveTo::SetAcceleration(float acceleration) {
    m_acceleration = acceleration;
}

class MoveAndRotateTo : public MoveTo {
public:
    MoveAndRotateTo (glm::vec2 pos, float speed, bool relative, bool immediate, float angle, bool angleRelative);
    void Start() override;
    void Run (float dt) override;
private:
    float m_deltaAngle;
    bool m_angleRelative;
    float m_initAngle;
    float m_endAngle;
    float m_angle;
};

class MoveAccelerated : public TargetActivity {
public:
    MoveAccelerated(
        glm::vec2 initialVelocity,
        glm::vec2 acceleration,
        float yStop,
        float rotationSpeed,
        float finalRotation);

    void Start() override;

    void Run(float dt) override;

private:
    float m_yStop;
    glm::vec2 m_initialVelocity;
    glm::vec2 m_velocity;
    glm::vec2 m_acceleration;
    float m_angle;
    float m_rotationSpeed;
    float m_finalRotation;
};