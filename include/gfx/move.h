#pragma once

#include <gfx/activity.h>
#include <gfx/entity.h>

class MoveTo : public Activity {
public:
    MoveTo(int activityId, Entity*, glm::vec2 pos, float speed);
    void Start() override;
    void Run (float dt) override;
private:
    Entity* m_entity;
    glm::vec2 m_toPos;
    glm::vec2 m_velocity;
    float m_speed;
    float m_lengthToCover;
    float m_lengthCovered;
};