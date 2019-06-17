#pragma once

#include <gfx/components/statemachine.h>
// this include walk and idle which is a special
// case of walk with target speed = 0
// goes to jump state if it does not touch below.

// walk handles the following animanitions:
// idle -- when no button is pressed, and horizontal velocity is below eps
// walk -- when button is pressed and horizontal velocity has same direction as button
// turn -- when button is pressed and horizontal velocity has opposite direction than button

//#include <platformer/states/platformerstate.h>
//#include <glm/glm.hpp>
//
//class Controller2D;
//class Renderer;
//
//class Idle2D : public PlatformerState {
//public:
//    Idle2D(float accelerationTimeGrounded);
//    bool Run (double) override;
//private:
//    float m_accTimeGnd;
//    float m_velocitySmoothing;
//};