#pragma once

#include <platformer/states/hitbase.h>
#include <platformer/states/jump2d.h>

class HitJump : public HitBase {
public:
    HitJump (const std::string& anim, float speed, float acceleration);
    HitJump (const HitJump& orig);
    void Run(double) override;
    void End () override {}
    std::shared_ptr<State> clone() const override;
private:
    float m_acceleration;
    float m_speed;
};

