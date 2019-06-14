#pragma once

#include <platformer/states/platformerstate.h>

class Jump2D : public PlatformerState {
public:
    Jump2D(float accelerationTimeAirborne, float speed, bool fliph, const std::string& anim, bool bounce, float bounceFactor);
    Jump2D (const Jump2D& orig);
    std::shared_ptr<State2> clone() const override;
    //void Start() override;
    void Run (double) override;
    void Init () override ;
    void End () override {}
private:
    float m_speed;
    float m_accTimeAir;
    float m_velocitySmoothing;
    bool m_flipHorizontally;
    //bool m_setJumpDownAnim;
    bool m_goingUp;
    bool m_bounce;
    float m_bounceFactor;
    std::string m_jumpAnim;
    //std::string m_jumpDownAnim;
};