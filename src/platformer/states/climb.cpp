#include "climb.h"

#include <monkey/math/geom.h>

#include <monkey/entity.h>
#include <monkey/components/controller3d.h>
#include <monkey/components/inputmethod.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/components/animator.h>
#include <monkey/components/statemachine.h>
#include <GLFW/glfw3.h>



Climb::Climb(const ITab& t) : State(t), m_animator(nullptr)  {
    m_speed = t.get<float>("speed");
}

void Climb::Init(const ITab& t) {
    m_entity->SetFlipX(false);
    auto ladder = t["ladder"];
    m_animator->SetAnimation("climb");
    float x = ladder->get<float>("x");
    m_yMin = ladder->get<float>("y_min");
    m_yMax = ladder->get<float>("y_max");
    m_yMin_goto = ladder->get<glm::vec3>("y_min_goto");
    m_yMax_goto = ladder->get<glm::vec3>("y_max_goto");
    int dir = t.get<int>("dir");
    auto pos = m_entity->GetPosition();
    pos.x = x;
    pos.y = (dir == 0) ? m_yMin + 0.1f : m_yMax - 0.1f;
    m_entity->SetPosition(pos);
}

void Climb::End() {

}

void Climb::Run (double dt) {
    // we might want to add the possibility of moving sideways
    bool left = m_input->isKeyDown(GLFW_KEY_LEFT);
    bool right = m_input->isKeyDown(GLFW_KEY_RIGHT);
    bool up = m_input->isKeyDown(GLFW_KEY_UP);
    bool down = m_input->isKeyDown(GLFW_KEY_DOWN);

    float targetVelocityX = 0.0f;
    float targetVelocityY = 0.0f;
    if (m_xMoveAllowed) {
        // ...
    }
    glm::vec3 velocity (0.0f);
    if (up || down) {
        velocity.y = (up ? 1.0f : -1.0f) * m_speed;
    }

    glm::vec3 delta = static_cast<float>(dt) * velocity;
    m_controller->Move(delta);
    m_animator->setActive(up || down );
    auto pos = m_entity->GetPosition();
    if (down && pos.y <= m_yMin) {
        m_entity->SetPosition(m_yMin_goto);
        m_sm->SetState("walk");
    }
    if (up && pos.y >= m_yMax) {
        m_entity->SetPosition(m_yMax_goto);
        m_sm->SetState("walk");
    }
}




void Climb::AttachStateMachine(StateMachine * sm) {
    State::AttachStateMachine(sm);
    m_entity = sm->GetObject();
    m_controller = dynamic_cast<Controller3D*>(m_entity->GetComponent<IController>());
    if (m_controller == nullptr) {
        GLIB_FAIL("Platformer state requires a <Controller3D> component!");
    }
    m_animator = m_entity->GetComponent<IAnimator>();
    m_input = m_entity->GetComponent<InputMethod>();
}