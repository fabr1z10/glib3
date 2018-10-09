#pragma once

#include <gfx/state.h>
#include <glm/glm.hpp>

class Renderer;


class AIWalk : public StateBehaviour {
public:
    AIWalk(const std::string& targetId, float speed) : StateBehaviour(), m_speed(speed), m_targetId{targetId} {}
    void Init (Entity*) override;
    bool Run(double) override;
private:
    Entity* m_entity;
    Entity* m_target;
    Renderer* m_renderer;
    float m_speed;
    std::string m_targetId;
    glm::vec2 m_offset;
    float m_eps;
};

