#pragma once

#include <gfx/platformerstate.h>
#include <glm/glm.hpp>
#include "platformerstate.h"

class Controller2D;
class Renderer;

class Idle2D : public PlatformerState {
public:
    Idle2D(const std::string& anim, float accelerationTimeGrounded);
    bool Run (double) override;
private:
    float m_accTimeGnd;
    float m_velocitySmoothing;
};