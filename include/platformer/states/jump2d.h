#pragma once

#include <platformer/states/platformerstate.h>
#include <glm/glm.hpp>

class Controller2D;
class Renderer;

class Jump2D : public PlatformerState {
public:
    Jump2D(const std::string& anim, float accelerationTimeAirborne, float speed);
    void Start() override;
    bool Run (double) override;
private:
    float m_speed;
    float m_accTimeAir;
    float m_velocitySmoothing;
};