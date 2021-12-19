#include <monkey/states/playerjump.h>
#include <GLFW/glfw3.h>
#include <monkey/math/geom.h>
#include <monkey/entity.h>


PlayerJump::PlayerJump(const ITab& t) : State(t) {
    m_maxSpeed = t.get<float>("max_speed");
    auto tmax = t.get<float>("time_acc");
    m_acceleration = m_maxSpeed / tmax;
    m_gravity = t.get<float>("gravity");
    m_walkState = t.get<std::string>("walk_state", "walk");
    m_jumpUpAnim = t.get<std::string>("jump_up_anim", "jump");
    m_jumpDownAnim = t.get<std::string>("jump_down_anim", "jump");
}

void PlayerJump::AttachStateMachine(StateMachine * sm) {

    State::AttachStateMachine(sm);
    m_entity = sm->GetObject();

    m_dynamics = m_entity->GetComponent<Dynamics>();
    if (m_dynamics == nullptr) {
        GLIB_FAIL("player jump state requires a dynamics component!");
    }

    //m_animator = m_entity->GetComponent<Animator>();
    m_input = m_entity->GetComponent<InputMethod>();
    if (m_input == nullptr) {
        GLIB_FAIL("player jump state requires a input method component!");
    }

    m_controller = (m_entity->GetComponent<IController>());
    if (m_controller == nullptr) {
        GLIB_FAIL("Platformer state requires a <Controller2D> component!");
    }

    m_renderer = dynamic_cast<AnimationRenderer*>(m_entity->GetComponent<Renderer>());

}

void PlayerJump::Init(const ITab &d) {

}

void PlayerJump::Run(double dt) {
    float dtf = static_cast<float>(dt);

    if (m_controller->grounded() && m_dynamics->m_velocity.y < 0) {
        // landed on a platform
        m_dynamics->m_velocity.y = 0.0f;

        m_sm->SetState(m_walkState);
        return;
    }

    // bump head
    if (m_controller->ceiling()) {
        m_dynamics->m_velocity.y = 0;
    }


    bool left = m_input->isKeyDown(GLFW_KEY_LEFT);
    bool right = m_input->isKeyDown(GLFW_KEY_RIGHT);
    glm::vec2 a;
    a.y = -m_gravity;

    if (left || right) {
        a.x = m_acceleration;
        m_entity->SetFlipX(left);
    } else {
        // apply deceleration only if velocity above theshold
        if (fabs(m_dynamics->m_velocity.x) > 0.1f) {
            a.x = -m_acceleration;
        } else {
            a.x = 0.0f;
            m_dynamics->m_velocity.x = 0.0f;
        }
    }

    m_dynamics->m_velocity += a * dtf;
    // limit horizontal vel to max speed
    if (left || right) {
        if (fabs(m_dynamics->m_velocity.x > m_maxSpeed)) {
            m_dynamics->m_velocity.x = sign(m_dynamics->m_velocity.x) * m_maxSpeed;
        }
    }
    //std::cerr << m_dynamics->m_velocity.x << "\n";
    auto delta = glm::vec3(m_dynamics->m_velocity * dtf, 0.0f);
    //m_entity->MoveLocal(delta);
    m_controller->Move(delta);
    if (m_renderer != nullptr) {
        if (m_dynamics->m_velocity.y >= 0) {
            m_renderer->setAnimation(m_jumpUpAnim);
        } else {
            m_renderer->setAnimation(m_jumpDownAnim);
        }
    }
}

void PlayerJump::End() {

}