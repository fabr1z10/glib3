#pragma once

#include <gfx/components/statemachine.h>
#include <glm/glm.hpp>

class Renderer;


class AIWalk : public State {
public:
    AIWalk(const std::string& targetId, float speed) : State(), m_speed(speed), m_targetId{targetId} {}
    void Start () override;
    void End() override {}
    bool Run(double) override;
private:
    Entity* m_target;
    Renderer* m_renderer;
    float m_speed;
    std::string m_targetId;
    glm::vec2 m_offset;
    float m_eps;
};

