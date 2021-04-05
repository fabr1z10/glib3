#include "keymovef.h"
#include <monkey/components/inputmethod.h>
#include <monkey/components/icontroller.h>
#include <monkey/entity.h>
#include <GLFW/glfw3.h>

KeyMoveF::KeyMoveF(const ITab& t) : State(t) {
	m_speed = t.get<float>("speed");
}

void KeyMoveF::Run (double dt) {

	bool left = m_input->isKeyDown(GLFW_KEY_LEFT);          // rotate ccw
	bool right = m_input->isKeyDown(GLFW_KEY_RIGHT);        // rotate cw
	bool up = m_input->isKeyDown(GLFW_KEY_UP);              // go fwd (x axis)
	bool down = m_input->isKeyDown(GLFW_KEY_DOWN);          // go backward (x axis)

	m_entity->SetFlipX(left);
	glm::vec3 move(0.0f);
	move.x = (left || right) ? m_speed : 0.0f;
	move.y = (up || down) ? (up ? m_speed : -m_speed) : 0.0f;
	m_controller->Move(move);


}

void KeyMoveF::Init(pybind11::dict&) {

}

void KeyMoveF::End() {

}
void KeyMoveF::AttachStateMachine(StateMachine * sm) {
	State::AttachStateMachine(sm);
	m_entity = sm->GetObject();
	m_input = m_entity->GetComponent<InputMethod>();
	m_controller = m_entity->GetComponent<IController>();

}