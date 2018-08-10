#pragma once

#include <gfx/activity.h>
#include <gfx/entity.h>

class MoveTo : public Activity {
public:
    MoveTo(Entity* entity, glm::vec2 pos, float speed, bool relative, bool immediate);
    MoveTo(const std::string& actorId, glm::vec2 pos, float speed, bool relative, bool immediate);
    void Start() override;
    void Run (float dt) override;
private:
    Entity* m_entity;
    glm::vec2 m_toPos;
    glm::vec2 m_velocity;
    float m_speed;
    float m_lengthToCover;
    float m_lengthCovered;
    bool m_relative;
    bool m_immediate;
    std::string m_actorId;
};