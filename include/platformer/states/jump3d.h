#pragma once

#include <platformer/states/platformerstate.h>

class Jump3D : public PlatformerState {
public:
    Jump3D(float accelerationTimeAirborne, float speed, bool fliph, const std::string& animUp, const std::string& animDown, bool bounce, float bounceFactor);
    Jump3D (const Jump3D& orig);
    std::shared_ptr<State> clone() const override;
    //void Start() override;
    void Run (double) override;
    void Init () override ;
    void End () override {}
    void ModifyAnimation() override;
    void ResetAnimation() override;
private:
    float m_speed;
    float m_accTimeAir;
    //float m_velocitySmoothing;
    bool m_flipHorizontally;
    //bool m_setJumpDownAnim;
    //bool m_goingUp;
    bool m_bounce;
    float m_bounceFactor;
    std::string m_jumpAnimUp;
    std::string m_jumpAnimDown;
    float m_vy0;
    //std::string m_jumpDownAnim;
};
