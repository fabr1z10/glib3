#include <monkey/states/foewalk25.h>
#include <monkey/monkey.h>
#include <monkey/entity.h>
#include <monkey/math/geom.h>
#include <monkey/components/controller25.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/components/animator.h>
#include <monkey/random.h>

FoeWalk25::FoeWalk25(const ITable & t) : State(t) {
    m_speed = t.get<float>("speed");
    m_acceleration = t.get<float>("acceleration");
    m_flipHorizontal = t.get<bool>("flipH");
    m_sdelta = t.get<float>("delta");
}

FoeWalk25::FoeWalk25(const FoeWalk25 & orig) : State(orig) {

}

std::shared_ptr<State> FoeWalk25::clone() const {
    return std::make_shared<FoeWalk25>(*this);
}


void FoeWalk25::Run(double dt) {
    auto playerPos = m_player->GetPosition();
    auto pos = m_entity->GetPosition();
    bool rightOfPlayer = playerPos.x < pos.x;
    float targetX = playerPos.x + (rightOfPlayer ? m_delta : -m_delta);

    float playerDepth = m_pc->getDepth();
    std::cerr << "player depth = " <<playerDepth << "\n";
    float meDepth = m_controller->getDepth();
    float dx = targetX - pos.x;
    float dd = playerDepth - meDepth;


    m_entity->SetFlipX(rightOfPlayer);

    float targetVelocityX = (abs(dx) < 1.0f) ? 0.0f : m_speed;
    float targetVelocityZ = (abs(dd) < 1.0f) ? 0.0f : sign(dd) * m_speed;

    if (targetVelocityX != 0.0f or targetVelocityZ != 0.0f) {
        glm::vec3 delta = m_dynamics->step(dt, targetVelocityX, targetVelocityZ, m_acceleration);
        glm::vec3 deltaH(delta.x, delta.y, delta.z);
        m_controller->Move(deltaH);
        m_animator->SetAnimation("walk");
    } else {
        m_animator->SetAnimation("idle");

        float f = Random::get().GetUniformReal(0.0f, 1.0f);
        if (f < 0.02f) {
            m_sm->SetState("attack");
        }
    }
    //std::cerr << "new z = " << m_entity->GetPosition().z << "\n";
    //UpdateAnimation();
    //std::cerr << deltaH.x << " " << deltaH.y << deltaH.z << "\n";
//    if (m_controller->grounded()) {
//        if (glm::length(glm::vec2(delta.x, delta.z)) > 0.2f) {
//            m_animator->SetAnimation("walk");
//        } else {
//            m_animator->SetAnimation("idle");
//        }
//    } else {
//        m_animator->SetAnimation("jump");
//    }

}


void FoeWalk25::Init(pybind11::dict &) {
}

void FoeWalk25::End() {
}

void FoeWalk25::AttachStateMachine(StateMachine * sm) {
    State::AttachStateMachine(sm);
    m_entity = sm->GetObject();

    m_player = Monkey::get().Get<Entity>("player");
    m_pc = dynamic_cast<Controller25*>(m_player->GetComponent<IController>());
    m_dynamics = m_entity->GetComponent<Dynamics2D>();
    m_controller = dynamic_cast<Controller25*>(m_entity->GetComponent<IController>());
    m_animator = m_entity->GetComponent<IAnimator>();
    m_delta = m_sdelta* m_entity->GetScale();
}