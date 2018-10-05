#pragma once

#include <gfx/platformerstate.h>
#include <glm/glm.hpp>
#include "platformerstate.h"

class Controller2D;
class Renderer;

class Walk2D : public PlatformerState {
public:
    Walk2D(const std::string& anim, float accelerationTimeGrounded, float gravity, float speed);
    bool Run (double) override;
private:
    glm::vec2 m_velocity;
    float m_gravity;
    float m_speed;
    float m_accTimeGnd;
    float m_velocitySmoothing;
};