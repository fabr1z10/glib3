#include <monkey/states/fly.h>
#include <GLFW/glfw3.h>
#include <monkey/math/geom.h>
#include <monkey/entity.h>


Fly::Fly(float gravity, glm::vec2 initialVelocity, float angularSpeed) : State(),
    m_initialVelocity{initialVelocity}, m_angularSpeed{angularSpeed}, m_gravity{gravity} {
}

Fly::Fly(const ITab& t) : State(t) {
    m_initialVelocity = t.get<glm::vec2>("initial_velocity");
    m_angularSpeed = t.get<float>("angular_speed", 0.0f);
    m_gravity = t.get<float>("gravity");
}

void Fly::AttachStateMachine(StateMachine * sm) {

    State::AttachStateMachine(sm);
    m_entity = sm->GetObject();

    m_dynamics = m_entity->GetComponent<Dynamics>();
    if (m_dynamics == nullptr) {
        GLIB_FAIL("player jump state requires a dynamics component!");
    }

    m_controller = (m_entity->GetComponent<IController>());
    if (m_controller == nullptr) {
        GLIB_FAIL("Platformer state requires a <Controller2D> component!");
    }

}

void Fly::Init(const ITab &d) {
    m_dynamics->m_velocity = m_initialVelocity;
}

void Fly::Run(double dt) {
    auto dtf = static_cast<float>(dt);
    m_entity->MoveLocal(m_initialVelocity*dtf);
    return;

    if (m_controller->grounded()) {
        return;
    }

    glm::vec2 a(0.0f);
    a.y = -m_gravity;
    m_dynamics->m_velocity += a * dtf;

    auto delta = glm::vec3(m_dynamics->m_velocity * dtf, 0.0f);
    m_controller->Move(delta);

}

void Fly::End() {

}