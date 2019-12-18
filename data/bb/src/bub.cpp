#include "bub.h"
#include <gfx/listener.h>
#include <gfx/components/inputmethod.h>
#include <iostream>
#include <gfx/components/stateactions.h>
#include <gfx/components/ianimator.h>
#include <gfx/entity.h>

BubWalk::BubWalk(luabridge::LuaRef fc, float speed, float acceleration, bool fliph, float jumpSpeed) :
    WalkSide(speed, acceleration, fliph, jumpSpeed), m_f(fc) {}


BubWalk::BubWalk(const BubWalk &orig) : WalkSide(orig), m_isShooting(false), m_f(orig.m_f) {}

std::shared_ptr<State> BubWalk::clone() const {
    return std::make_shared<BubWalk>(*this);
}

void BubWalk::AttachStateMachine(StateMachine * sm) {
    PlatformerState::AttachStateMachine(sm);

    AddKey(341, std::make_shared<StateFunc>([&] () {
        shoot();
    }));
}

void BubWalk::shoot() {
    m_animator->SetAnimation("shoot");
    m_isShooting = true;
    // make the bubble
    glm::vec3 pos = m_entity->GetPosition();
    m_f(pos.x, pos.y, pos.z);

}

void BubWalk::ModifyAnimation() {
    if (m_isShooting) {
        if (m_animator->IsComplete()) {
            m_isShooting = false;
        }
    } else {
        WalkSide::ModifyAnimation();

    }


}