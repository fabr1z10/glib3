#include <monkey/states/jumpattack.h>
#include <monkey/entity.h>
#include <GLFW/glfw3.h>
#include <monkey/components/inputmethod.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/components/controller2d.h>
#include <monkey/components/ianimator.h>

JumpAttack::JumpAttack(const ITable &t) : PlatformerState(t) {
    m_speed = t.get<float>("speed");
    m_accTimeAir = t.get<float>("acceleration");
    m_flipHorizontally = t.get<bool>("flipH");

    m_anim = t.get<std::string>("anim");
}


void JumpAttack::Run(double dt) {

    if (m_animator->IsComplete()) {
        m_sm->SetState("jump");
    }

    bool left = m_input->isKeyDown(GLFW_KEY_LEFT);
    bool right = m_input->isKeyDown(GLFW_KEY_RIGHT);

    float vy0 = m_dynamics->m_velocity.y;

    // if player lands on a platform, just switch to 'walk' state
    if (m_controller->grounded() && m_dynamics->m_velocity.y < 0) {
        m_dynamics->m_velocity.y = 0.0f;
        m_sm->SetState("walk");
        return;
    }

    // bump head
    if (m_controller->ceiling()) {
        m_dynamics->m_velocity.y = 0;
        m_sm->SetState("jump");
    }

    float targetVelocityX = 0.0f;
    if (left || right) {
        if (m_flipHorizontally) {
            m_entity->SetFlipX(left);
            targetVelocityX = m_speed;
        } else {
            targetVelocityX = (left ? -1.0f : 1.0f) * m_speed;
        }

    }
    glm::vec3 delta = m_dynamics->step(dt, targetVelocityX, m_accTimeAir);

    m_controller->Move(delta);

}


void JumpAttack::Init(pybind11::dict& d) {
    std::string anim = m_anim;
    if (!d.empty()) {
        anim = d["anim"].cast<std::string>();
    }
    m_animator->SetAnimation(anim);

}


//void JumpAttack::AttachStateMachine(StateMachine * sm) {
//    PlatformerState::AttachStateMachine(sm);
//    auto entity = sm->GetObject();
//    m_animator = entity->GetComponent<IAnimator>();
//    m_input = entity->GetComponent<InputMethod>();
//
//
//}