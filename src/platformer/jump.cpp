#include <platformer/jump.h>

#include <gfx/components/controller2d.h>
#include <gfx/components/animator.h>
#include <gfx/components/inputmethod.h>
#include <gfx/components/dynamics2d.h>

#include <gfx/entity.h>
#include <gfx/math/geom.h>

#include <GLFW/glfw3.h>


Jump::Jump(float speed, float acceleration, const std::string& jumpUp, const std::string& jumpDown) :
State2(), m_speed(speed), m_acceleration(acceleration), m_anims{jumpUp, jumpDown}, m_prevAnimFlag(-1), m_colliderId("walk")  {}

Jump::Jump(const Jump & orig) :State2(orig) {
    m_speed = orig.m_speed;
}


std::shared_ptr<State2> Jump::clone() const {
    return std::make_shared<Jump>(*this);
}

void Jump::UpdateAnimation() {
    m_animFlag = m_dynamics->m_velocity.y >=0 ? 0 : 1;
    if (m_prevAnimFlag != m_animFlag) {
        m_prevAnimFlag = m_animFlag;
        m_stateMachine->SetAnimation(m_anims[m_animFlag]);
    }
}

void Jump::AttachStateMachine(StateMachine2* sm) {
    m_stateMachine = dynamic_cast<CharacterStateMachine*>(sm);
    m_entity = sm->GetObject();
    m_controller = m_entity->GetComponent<Controller2D>();
    m_animator = m_entity->GetComponent<Animator>();
    m_input = m_entity->GetComponent<InputMethod>();
    m_dynamics = dynamic_cast<Dynamics2D*>(m_entity->GetComponent<Properties>());

}

void Jump::Init() {
    m_prevAnimFlag = -1;
    m_velocitySmoothing=0.0f;
    UpdateAnimation();
    m_stateMachine->SetCollider(m_colliderId);
}

void Jump::Run(double dt) {
    bool left =m_input->isKeyDown(GLFW_KEY_LEFT);
    bool right =m_input->isKeyDown(GLFW_KEY_RIGHT);

    if (m_controller->m_details.below && m_dynamics->m_velocity.y < 0) {
        m_dynamics->m_velocity.y = 0.0f;
        m_stateMachine->SetState("walk");
        return;
    }

    // bump head
    if (m_controller->m_details.above)	{
        m_dynamics->m_velocity.y = 0;
    }

    // apply gravity
    m_dynamics->m_velocity.y += m_dynamics->m_gravity * dt;

//    if (m_goingUp && m_dynamics->m_velocity.y < 0) {
//        m_goingUp = false;
//        if (m_setJumpDownAnim) {
//            m_renderer->SetAnimation(m_jumpDownAnim);
//        }
//    }
//
//
    float targetVelocityX = 0.0f;
    if (left || right) {
        m_entity->SetFlipX(left);
        targetVelocityX = m_speed;
        //m_renderer->SetFlipX(true);
    }
    m_dynamics->m_velocity.x = SmoothDamp(
            m_dynamics->m_velocity.x, targetVelocityX,
            m_velocitySmoothing,
            m_acceleration, dt);
    glm::vec2 delta = static_cast<float>(dt) * m_dynamics->m_velocity;
    m_controller->Move(delta);

}