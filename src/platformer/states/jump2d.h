#pragma once

#include <monkey/states/platformerstate.h>

class Jump2D : public PlatformerState {
public:
    Jump2D(float accelerationTimeAirborne, float speed, bool fliph, const std::string& animUp, const std::string& animDown, bool bounce, float bounceFactor);
    Jump2D(const ITab&);
    //void Start() override;
    void Run (double) override;
    void Init (const ITab&) override ;
    void End () override {}
    void ModifyAnimation() override;
    void ResetAnimation() override;
    void setWalkState (const std::string& state);
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
    std::string m_walkState;
    //std::string m_jumpDownAnim;
};

inline void Jump2D::setWalkState(const std::string &state) {
    m_walkState =state;
}
