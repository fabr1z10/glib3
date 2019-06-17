#pragma once

#include <platformer/states/platformerstate.h>
#include <platformer/states/jump2d.h>
class Shape;

// this is the walk state used in platformers like SuperMario
class Hit : public PlatformerState {
public:
    /**
     *
     * @param speed The maximum speed
     * @param acceleration The acceleration
     * @param fliph Flip entity horizontally when going left
     */
    Hit (const std::string& anim, int frame, std::shared_ptr<Shape> attackBox);
    Hit (const Hit& orig);
    void Run(double) override;
    void Init () override;
    void End () override {}
    std::shared_ptr<State> clone() const override;
private:
    std::string m_anim;
    int m_frame;
    std::shared_ptr<Shape> m_box;
};

//// this is the walk state used in platformers like SuperMario
//class HitJump : public Jump2D {
//public:
//    /**
//     *
//     * @param speed The maximum speed
//     * @param acceleration The acceleration
//     * @param fliph Flip entity horizontally when going left
//     */
//    HitJump (float accelerationTimeAirborne, float speed, bool flipH, const std::string& anim, bool bounce, float bounceFactor, int frame, std::shared_ptr<Shape> attackBox);
//    HitJump (const HitJump& orig);
//    void Run(double) override;
//    void Init () override;
//    void End () override {}
//    std::shared_ptr<State> clone() const override;
//private:
//    std::string m_anim;
//    int m_frame;
//    std::shared_ptr<Shape> m_box;
//};