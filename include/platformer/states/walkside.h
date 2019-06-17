#pragma once

#include <platformer/states/platformerstate.h>

class Controller2D;
class Dynamics2D;
class InputMethod;

// this is the walk state used in platformers like SuperMario
class WalkSide : public PlatformerState {
public:
    /**
     *
     * @param speed The maximum speed
     * @param acceleration The acceleration
     * @param fliph Flip entity horizontally when going left
     */
    WalkSide (float speed, float acceleration, bool fliph, float jumpSpeed);
    WalkSide (const WalkSide& orig);
    void Run(double) override;
    void Init () override;
    void End () override;
    std::shared_ptr<State> clone() const override;
private:
    bool m_flipHorizontally;
    float m_speed;
    float m_acceleration;
    float m_velocitySmoothing;
    float m_jumpSpeed;
};