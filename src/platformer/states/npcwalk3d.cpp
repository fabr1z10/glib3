#include "npcwalk3d.h"
#include <monkey/components/controller3d.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/components/animator.h>
#include <monkey/components/statemachine.h>



NPCWalk3D::NPCWalk3D(const ITab& t) : State(t), m_animator(nullptr)  {
    auto factory = Engine::get().GetSceneFactory();
    m_speed = t.get<float>("speed");
    m_acceleration = t.get<float>("acceleration");
    m_flipHorizontally = t.get<bool>("flipH");
    m_jumpSpeed = t.get<float>("jumpSpeed");
    auto pi = t["animator"];
    m_walkAnimator = factory->make2<WalkAnim>(*pi);
}

void NPCWalk3D::Init(const ITab&) {
    m_controller->m_details.below= true;
    m_dynamics->m_velocity = glm::vec3(0.0f);
    m_currentSegment = 0;
    m_path.push_back(glm::vec2(50.0f, 0.0f));
    m_targetVelocity = glm::normalize(m_path[m_currentSegment]) * m_speed;
}

void NPCWalk3D::End() {

}
void NPCWalk3D::Run (double dt) {

    if (!m_controller->grounded()) {
        glm::vec3 delta = m_dynamics->step(dt, 0.0, 0.0f, m_acceleration);
        m_controller->Move(delta);
        //m_sm->SetState("jump");
        return;
    } else {
        m_dynamics->m_velocity.y = 0.0f;
    }

    if (m_controller->m_details.right || m_controller->m_details.left) {
        m_dynamics->m_velocity.x = 0.0f;

    }
    glm::vec2 currentDirection = m_path[m_currentSegment];
    glm::vec3 delta =m_dynamics->step(dt, m_targetVelocity[0], m_targetVelocity[1], m_acceleration);
    m_controller->Move(delta);
    m_walkAnimator->animate(m_animator, m_dynamics->m_velocity);
}

void NPCWalk3D::AttachStateMachine(StateMachine * sm) {
    State::AttachStateMachine(sm);
    m_entity = sm->GetObject();
    m_controller = dynamic_cast<Controller3D*>(m_entity->GetComponent<IController>());
    if (m_controller == nullptr) {
        GLIB_FAIL("Platformer state requires a <Controller3D> component!");
    }
    m_animator = m_entity->GetComponent<IAnimator>();
    m_dynamics = m_entity->GetComponent<Dynamics2D>();
    if (m_dynamics == nullptr) {
        GLIB_FAIL("Platormer state requires a <Dynamics2D> component!");
    }



}