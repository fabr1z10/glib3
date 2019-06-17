//#include <platformer/walk.h>
//
//#include <gfx/components/controller2d.h>
//#include <gfx/components/animator.h>
//#include <gfx/components/inputmethod.h>
//#include <gfx/components/dynamics2d.h>
//
//#include <gfx/error.h>
//#include <gfx/math/geom.h>
//#include <gfx/entity.h>
//#include <GLFW/glfw3.h>
//
//
//extern GLFWwindow* window;
//
//std::shared_ptr<State> Walk::clone() const {
//    return std::make_shared<Walk>(*this);
//}
//
//
//void Walk::UpdateAnimation(bool left, bool right) {
//    if (!left && !right) {
//        m_animFlag = 0;
//    } else {
//        m_animFlag = ((left && m_dynamics->m_velocity.x < 0) || (right && m_dynamics->m_velocity.x > 0)) ? 1 : 2;
//    }
//    if (m_prevAnimFlag != m_animFlag) {
//        m_prevAnimFlag = m_animFlag;
//        m_sm->SetAnimation(m_anims[m_animFlag]);
//    }
//}
//
//void Walk::AttachStateMachine(StateMachine* sm) {
//    m_sm = dynamic_cast<CharacterStateMachine*>(sm);
//    m_entity = sm->GetObject();
//    m_controller = m_entity->GetComponent<Controller2D>();
//    m_dynamics = dynamic_cast<Dynamics2D*>(m_entity->GetComponent<Properties>());
//    //m_animator = m_entity->GetComponent<Animator>();
//    m_input = m_entity->GetComponent<InputMethod>();
//    if (m_input == nullptr) {
//        GLIB_FAIL("Walk state requires an input method component attached!");
//    }
//    // when walking, I want to know when the user press the up key, because this allows me to jump
//}
//
//void Walk::KeyListener(int key) {
//    if (m_canDuck && key == GLFW_KEY_DOWN) {
//        m_sm->SetState("duck");
//    }
//
//    if (key == GLFW_KEY_UP) {
//        // set jump speed
//        m_dynamics->m_velocity.y = m_jumpVelocity;
//        m_sm->SetState("jump");
//    }
//}
//
//void Walk::Init() {
//    m_prevAnimFlag = -1;
//    m_velocitySmoothing=0.0f;
//    bool left =m_input->isKeyDown(GLFW_KEY_LEFT);
//    bool right =m_input->isKeyDown(GLFW_KEY_RIGHT);
//    UpdateAnimation(left, right);
//    m_sm->SetCollider(m_colliderId);
//
//}
//
//void Walk::Run (double dt) {
//    if (!m_controller->m_details.below) {
//        m_sm->SetState("jump");
//        return;
//    }
//
//    bool left = m_input->isKeyDown(GLFW_KEY_LEFT);
//    bool right = m_input->isKeyDown(GLFW_KEY_RIGHT);
//
//    m_dynamics->m_velocity.y = m_dynamics->m_gravity * static_cast<float>(dt);
//    float targetVelocityX = 0.0f;
//
//    if (left || right) {
//        if (m_horizontalFlip) {
//            m_entity->SetFlipX(left);
//            targetVelocityX = m_speed;
//        } else {
//            targetVelocityX = (left ? -1.0f : 1.0f) * m_speed;
//        }
//
//    }
//
//    m_dynamics->m_velocity.x = SmoothDamp(m_dynamics->m_velocity.x, targetVelocityX, m_velocitySmoothing, m_acceleration, dt);
//    glm::vec2 delta = static_cast<float>(dt) * m_dynamics->m_velocity;
//    m_controller->Move(delta);
//
//    UpdateAnimation(left, right);
//
//}
