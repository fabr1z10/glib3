#pragma once

#include <platformer/states/platformerstate.h>
#include <glm/glm.hpp>

class Controller2D;
class Renderer;

class Walk2D : public PlatformerState {
public:
    Walk2D(const std::string& anim, float accelerationTimeGrounded, float speed);
    bool Run (double) override;
private:
    float m_speed;
    float m_accTimeGnd;
    float m_velocitySmoothing;
};

