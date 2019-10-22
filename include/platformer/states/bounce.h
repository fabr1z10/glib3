//#pragma once
//
//#include <platformer/states/platformerstate.h>
//
//class Controller2D;
//class Dynamics2D;
//class InputMethod;
//
//class Bounce : public PlatformerState {
//public:
//
//    Bounce (float speed, float acceleration);
//    Bounce (const Bounce& orig);
//    std::shared_ptr<State> clone() const override;
//
//    void Run(double) override;
//    void Init () override;
//    void End () override;
//    void ResetAnimation() override;
//    void ModifyAnimation() override;
//    void setWalkAnimation (const std::string& anim);
//    void setIdleAnimation (const std::string& anim);
//    void setJumpState (const std::string& state);
//private:
//    bool m_flipHorizontally;
//    float m_speed;
//    float m_acceleration;
//    float m_velocitySmoothing;
//    float m_jumpSpeed;
//    std::string m_walkAnim;
//    std::string m_jumpState;
//    std::string m_idleAnim;
//};
//
//inline void WalkSide::setWalkAnimation (const std::string& anim) {
//    m_walkAnim = anim;
//}
//
//inline void WalkSide::setIdleAnimation (const std::string& anim) {
//    m_idleAnim = anim;
//}
//
//inline void WalkSide::setJumpState (const std::string& state) {
//    m_jumpState = state;
//}
