#pragma once

#include <platformer/states/platformerstate.h>

// this is the walk state used in platformers like SuperMario
class Duck : public PlatformerState {
public:
    /**
     *
     * @param speed The maximum speed
     * @param acceleration The acceleration
     * @param fliph Flip entity horizontally when going left
     */
    Duck(float acceleration);

    Duck(const Duck &orig);

    void Run(double) override;

    void Init() override;

    void End() override {}

    std::shared_ptr<State> clone() const override;

    void ResetAnimation() override;

    void ModifyAnimation() override {}
private:
    float m_acceleration;
};