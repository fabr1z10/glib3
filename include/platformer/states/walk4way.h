#pragma once

#include <platformer/states/platformerstate.h>

class Controller2D;
class Dynamics2D;
class InputMethod;

class Walk4Way : public PlatformerState {
public:
    /**
     *
     * @param speed The maximum speed
     * @param acceleration The acceleration
     * @param fliph Flip entity horizontally when going left
     */
    Walk4Way (float speed, float acceleration, bool fliph);
    Walk4Way (const Walk4Way& orig);
    void Run(double) override;
    void Init () override;
    void End () override;
    std::shared_ptr<State> clone() const override;
private:
    bool m_flipHorizontally;
    float m_speed;
    float m_acceleration;
    float m_velocitySmoothing;
};