#pragma once

#include <gfx/platformerstate.h>
#include <glm/glm.hpp>
#include "platformerstate.h"

class Controller2D;
class Renderer;

class Jump2D : public PlatformerState {
public:
    Jump2D(const std::string& anim, float accelerationTimeAirborne, float gravity, float speed);
    bool Run (double) override;
private:
    glm::vec2 m_velocity;
    float m_gravity;
    float m_speed;
    float m_accTimeAir;
    float m_velocitySmoothing;
};