#pragma once

#include <platformer/states/hitbase.h>
#include <platformer/states/jump2d.h>

// this is the walk state used in platformers like SuperMario
class Hit : public HitBase {
public:
    /**
     *
     * @param speed The maximum speed
     * @param acceleration The acceleration
     * @param fliph Flip entity horizontally when going left
     */
    Hit (const std::string& anim, float acceleration);
    Hit (const Hit& orig);
    void Run(double) override;
    void End () override {}
    std::shared_ptr<State> clone() const override;
private:
    float m_acceleration;
};

