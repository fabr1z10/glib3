#pragma once

#include <gfx/statemachine.h>
#include <glm/glm.hpp>

class WalkState : public State {
public:
    WalkState(float speed);
    void Init() override {}

    bool Run(double) override;
private:
    float m_speed;
};

class WalkStateCollision : public State {
public:
    WalkStateCollision (float width, float height, float speed, int horizontalRays, int verticalRays);
    void Init() override;
    bool Run(double) override;
    void AddAnimation(const std::string& id, const std::string& name);
private:
    CollisionEngine* m_engine;
    Renderer* m_renderer;
    float m_width;
    float m_height;
    float m_speed;
    int m_horizontalRays;
    int m_verticalRays;
    float m_horizontalRaySpace;
    float m_verticalRaySpace;
    bool m_handleAnimations;
    glm::vec2 m_prevMove;
    std::unordered_map<std::string, std::string> m_animations;
};