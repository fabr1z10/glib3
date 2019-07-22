#pragma once

#include <platformer/states/platformerstate.h>

class Controller2D;
class Dynamics2D;
class InputMethod;

// this is the walk state used in platformers like SuperMario
class Walk3D : public PlatformerState {
public:
    /**
     *
     * @param speed The maximum speed
     * @param acceleration The acceleration
     * @param fliph Flip entity horizontally when going left
     */
    Walk3D (float speed, float acceleration, bool fliph, float jumpSpeed);
    Walk3D (const Walk3D& orig);
    void Run(double) override;
    void Init () override;
    void End () override;
    std::shared_ptr<State> clone() const override;
    void ResetAnimation() override;
    void ModifyAnimation() override;

private:
    bool m_flipHorizontally;
    float m_speed;
    float m_acceleration;
    float m_velocitySmoothing;
    float m_jumpSpeed;
};