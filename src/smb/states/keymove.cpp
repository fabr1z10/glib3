#include "keymove.h"
#include <monkey/components/inputmethod.h>
#include <monkey/entity.h>
#include <GLFW/glfw3.h>

KeyMove::KeyMove(const ITable & t) : State(t) {
    m_speed = t.get<float>("speed");
    m_rotationSpeed = t.get<float>("rotation_speed");

}

void KeyMove::Run (double dt) {

    bool left = m_input->isKeyDown(GLFW_KEY_LEFT);          // rotate ccw
    bool right = m_input->isKeyDown(GLFW_KEY_RIGHT);        // rotate cw
    bool up = m_input->isKeyDown(GLFW_KEY_UP);              // go fwd (x axis)
    bool down = m_input->isKeyDown(GLFW_KEY_DOWN);          // go backward (x axis)

    if (up) {
        m_entity->MoveLocal(glm::vec2(m_speed * dt, 0.0f));
    } else if (down) {
        m_entity->MoveLocal(glm::vec2(-m_speed * dt, 0.0f));
    }
    if (left) {
        m_entity->Rotate(m_rotationSpeed * dt, glm::vec3(0, 0, 1));
    } else if (right) {
        m_entity->Rotate(-m_rotationSpeed * dt, glm::vec3(0, 0, 1));

    }



}
void KeyMove::Init(pybind11::dict&) {

}

void KeyMove::End() {

}
void KeyMove::AttachStateMachine(StateMachine * sm) {
    State::AttachStateMachine(sm);
    m_entity = sm->GetObject();
    m_input = m_entity->GetComponent<InputMethod>();


}