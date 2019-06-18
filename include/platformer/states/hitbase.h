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
    HitBase (const std::string& anim, int frame, std::shared_ptr<Shape> attackBox, int mask, int tag);
    HitBase (const HitBase& orig);
    void Init () override;
    void End () override {}
    void AttachStateMachine(StateMachine * sm) override;

protected:
    void HandleCollision();

private:
    std::string m_anim;
    int m_frame;
    std::shared_ptr<Shape> m_box;
    CollisionEngine* m_collisionEngine;
    bool m_hitDone;
    int m_mask;
    int m_tag;

};
