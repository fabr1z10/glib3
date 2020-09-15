#include "jumpattack.h"
#include <monkey/components/ianimator.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/entity.h>
#include <monkey/components/icontroller.h>

JAttack::JAttack(const ITable & t) : PlatformerState(t) {
	m_animUp = t.get<std::string>("anim_up", "jumpup");
	m_animDown = t.get<std::string>("anim_down", "jumpdown");
	m_animLand = t.get<std::string>("anim_land");

	m_jumpHeight = t.get<float> ("jump_height");
	m_timeDown = t.get<float>("time_down", 1.0f);
	m_speedDown = m_jumpHeight / m_timeDown;
}

JAttack::JAttack(const JAttack & orig) : PlatformerState(orig) {
}

std::shared_ptr<State> JAttack::clone() const {
	return std::make_shared<JAttack>(*this);
}

void JAttack::End() {

}


void JAttack::AttachStateMachine(StateMachine * sm) {
	PlatformerState::AttachStateMachine(sm);
	m_target = Monkey::get().Get<Entity>("player");
}

void JAttack::Init(pybind11::dict &) {
	m_animator->SetAnimation(m_animUp);
	auto targetPos = m_target->GetPosition();
	auto mePos = m_entity->GetPosition();
	float dxToCover = targetPos.x - mePos.x;
	float jumpHeight = targetPos.y + m_jumpHeight - mePos.y;
	float jumpSpeed = sqrt (2.0 * jumpHeight * fabs(m_dynamics->m_gravity));

	float tja = (jumpSpeed / fabs(m_dynamics->m_gravity));
	m_targetVelocityX = dxToCover / tja;
	if (m_entity->GetFlipX()) {
		m_targetVelocityX *= -1.0f;
	}
	m_dynamics->m_velocity.y = jumpSpeed;
}

void JAttack::Run(double dt) {
	// if not touching the ground, set status to jump
	if (m_controller->grounded()) {
		if (m_dynamics->m_velocity.y < 0) {
			m_sm->SetState("walk");
		}
	} else {
		if (m_dynamics->m_velocity.y < 0) {
			m_animator->SetAnimation(m_animDown);
			m_targetVelocityX = 0.0f;
			m_dynamics->m_velocity.y = -m_speedDown;
		}
	}

	glm::vec3 delta = m_dynamics->step(dt, m_targetVelocityX, 0.0f);

	m_controller->Move(delta);
	UpdateAnimation();


}