#include <platformer/jump.h>
#include <gfx/components/controller2d.h>
#include <gfx/components/animator.h>
#include <gfx/entity.h>
#include <gfx/math/geom.h>

#include <GLFW/glfw3.h>

extern GLFWwindow* window;

Jump::Jump(float speed) : State2(), m_speed(speed){}
Jump::Jump(const Jump & orig) :State2(orig) {
    m_speed = orig.m_speed;
}


std::shared_ptr<State2> Jump::clone() const {
    return std::make_shared<Jump>(*this);
}



void Jump::AttachStateMachine(StateMachine2* sm) {
    m_stateMachine = (CharacterStateMachine*) dynamic_cast<CharacterStateMachine*>(sm);
    m_entity = sm->GetObject();
    m_controller = m_entity->GetComponent<Controller2D>();
    m_animator = m_entity->GetComponent<Animator>();
}

void Jump::Run(double dt) {
    int stateL = glfwGetKey(window, GLFW_KEY_LEFT);
    int stateR = glfwGetKey(window, GLFW_KEY_RIGHT);

    bool left = stateL == GLFW_PRESS;
    bool right = stateR == GLFW_PRESS;

//    // if not touching the ground, set status to jump
//    bool left = m_keyboard.isPressed(GLFW_KEY_LEFT);
//    bool right = m_keyboard.isPressed(GLFW_KEY_RIGHT);
//    if (left && right) left = false;
//
    if (m_controller->m_details.below && m_stateMachine->m_velocity.y < 0) {
        m_stateMachine->m_velocity.y = 0.0f;
        m_stateMachine->SetState("walk");
        return;
    }

    // bump head
    if (m_controller->m_details.above)	{
        m_stateMachine->m_velocity.y = 0;
    }

    // apply gravity
    m_stateMachine->m_velocity.y += m_stateMachine->m_gravity * dt;

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
    m_stateMachine->m_velocity.x = SmoothDamp(
            m_stateMachine->m_velocity.x, targetVelocityX,
            m_velocitySmoothing,
            m_stateMachine->m_accTimeAir, dt);
    glm::vec2 delta = static_cast<float>(dt) * m_stateMachine->m_velocity;
    m_controller->Move(delta);

}