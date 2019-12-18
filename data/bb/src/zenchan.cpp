#include "zenchan.h"
#include <iostream>
#include <gfx/scenefactory.h>
#include "factories.h"
#include <gfx/components/dynamics2d.h>
#include <gfx/components/controller2d.h>
#include <gfx/random.h>



ZenChanWalk::ZenChanWalk(bool left, float speedx, float speedy) : m_left(left), m_type(WalkType::GROUNDED), m_speedx(speedx),
    m_speedy(speedy), m_jumpHeight(48.0f) {}

ZenChanWalk::ZenChanWalk(const ZenChanWalk &orig) : State(orig) {}

std::shared_ptr<State> ZenChanWalk::clone() const {
    return std::make_shared<ZenChanWalk>(*this);
}

void ZenChanWalk::AttachStateMachine(StateMachine * sm) {
    State::AttachStateMachine(sm);
    m_entity = m_sm->GetObject();
    m_entity->SetFlipX(m_left);
    m_controller2D = dynamic_cast<Controller2D*>(m_entity->GetComponent<IController>());
    m_player = Ref::Get<Entity>("player").get();

}
void ZenChanWalk::Init() {
}


void ZenChanWalk::flip() {
    m_left = !m_left;
    m_entity->SetFlipX(m_left);

}
void ZenChanWalk::Run(double dt) {

    float py = m_player->GetPosition().y;
    float ey = m_entity->GetPosition().y;

    if ((m_left && m_controller2D->m_details.left) || (!m_left && m_controller2D->m_details.right)) {
        // I bumped into a wall
        if (m_type == WalkType::GROUNDED) {
            flip();
        } else {
            m_delta.x = 0.0f;
        }
    }

    if (m_type == WalkType::JUMPUP) {
        if (m_entity->GetPosition().y - m_jumpLevel >= m_jumpHeight) {
            m_type = WalkType::JUMPDOWN;
        }
    }

    if (!m_controller2D->grounded()) {
        if (m_type == WalkType::GROUNDED) {
            m_type = WalkType::JUMPDOWN;
            m_delta.x = 0.0f;
        }
        m_delta.y = (m_type == WalkType::JUMPUP ? m_speedy : -m_speedy);

    } else {
        m_type = WalkType::GROUNDED;
        m_delta.x = m_speedx;
        // if zenchan is grounded, then it can jump, if a platform is above AND the player is strictly above
        if (py > ey) {
            float r = Random::get().GetUniformReal(0, 1);
            if (r < 0.01) {
                m_type = WalkType::JUMPUP;
                m_delta.y = m_speedy;
                m_delta.x = 0;
                m_jumpLevel = m_entity->GetPosition().y;
            }
        }
        // check if I reached the end of the platform
        if (m_controller2D->IsFalling(m_left ? -1 : 1)) {
            if (py >= ey) {
                m_type = WalkType::JUMPUP;
                m_delta.y = m_speedy;
                m_jumpLevel = m_entity->GetPosition().y - m_jumpHeight*0.7f;
            }
        }
    }


    m_controller2D->Move(m_delta);

}

void ZenChanWalk::End() {
}

