#include "zenchan.h"
#include <iostream>
#include <gfx/scenefactory.h>
#include "factories.h"
#include <gfx/components/dynamics2d.h>
#include <gfx/components/controller2d.h>


extern "C" void hello(SceneFactory* f) {
    std::cout << "hello pano" << '\n';
    f->addStateFactory("zenchan", std::make_unique<ZenChanFactory>());
}

ZenChanState::ZenChanState(bool left, float speedx, float speedy) : m_left(left), m_speedx(speedx),
    m_speedy(speedy) {}

ZenChanState::ZenChanState(const ZenChanState &orig) : PlatformerState(orig) {}

std::shared_ptr<State> ZenChanState::clone() const {
    return std::make_shared<ZenChanState>(*this);
}

void ZenChanState::Init() {
    m_entity->SetFlipX(m_left);
    m_controller2D = dynamic_cast<Controller2D*>(m_entity->GetComponent<IController>());

}

void ZenChanState::Run(double dt) {
    float targetVelocityX = 0.0f;

    glm::vec3 delta (0.0f);

    if ((m_left && m_controller2D->m_details.left) || (!m_left && m_controller2D->m_details.right)) {
        // I bumped into a wall
        m_left = !m_left;
        m_entity->SetFlipX(m_left);
    }

    if (!m_controller->grounded()) {
        delta.y = -m_speedy;
    } else {
        delta.x = m_speedx;
    }
    m_controller->Move(delta);

}

void ZenChanState::End() {
}

void ZenChanState::ResetAnimation() {

}

void ZenChanState::ModifyAnimation() {
}