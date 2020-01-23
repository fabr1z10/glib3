#pragma once

#include "platformerstate.h"

// this is the walk state used in platformers like SuperMario
class FoeDead : public PlatformerState {
public:
    /**
     *
     * @param speed The maximum speed
     * @param acceleration The acceleration
     * @param fliph Flip entity horizontally when going left
     */
    FoeDead (float time);
    FoeDead (const FoeDead& orig);
    std::shared_ptr<State> clone() const override;

    void Run(double) override;
    void Init () override;
    void End () override;
    void ResetAnimation() override {}
    void ModifyAnimation() override {}
private:
    float m_time;
    float m_timer;
    int m_id;
};