#pragma once

#include <platformer/states/platformerstate.h>
#include <platformer/states/jump2d.h>

class Shape;
class CollisionEngine;

// this is the walk state used in platformers like SuperMario
class HitBase : public PlatformerState {
public:
    /**
     *
     * @param speed The maximum speed
     * @param acceleration The acceleration
     * @param fliph Flip entity horizontally when going left
     */
    HitBase (const std::string& anim);
    HitBase (const HitBase& orig);
    void Init () override;
    void End () override {}
    void AttachStateMachine(StateMachine * sm) override;
    void ResetAnimation() override;
    void ModifyAnimation() override {}
protected:
    void HandleCollision();

private:
    std::string m_anim;

};
