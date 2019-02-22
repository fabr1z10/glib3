//#pragma once
//
//#include <platformer/states/platformerstate.h>
//#include <glm/glm.hpp>
//
//class Controller2D;
//class Renderer;
//
//class Jump2D : public PlatformerState {
//public:
//    Jump2D(float accelerationTimeAirborne, float speed, bool setAnimDown, const std::string& animDown);
//    //void Start() override;
//    void ResetState() override;
//    bool Run (double) override;
//private:
//    float m_speed;
//    float m_accTimeAir;
//    float m_velocitySmoothing;
//    bool m_setJumpDownAnim;
//    bool m_goingUp;
//    std::string m_jumpDownAnim;
//};