#define GLM_ENABLE_EXPERIMENTAL

#include "jumpattack.h"
#include <glm/gtx/transform.hpp>
#include <monkey/components/ianimator.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/entity.h>
#include <monkey/engine.h>
#include <monkey/python/wrap1.h>
#include <monkey/components/controller2d.h>


JAttack::JAttack(const ITab& t) : PlatformerState(t) {
	m_animUp = t.get<std::string>("anim_up", "jumpup");
	m_animDown = t.get<std::string>("anim_down", "jumpdown");
	m_animLand = t.get<std::string>("anim_land");

	m_jumpHeight = t.get<float> ("jump_height");
	m_timeDown = t.get<float>("time_down", 1.0f);
	m_speedDown = m_jumpHeight / m_timeDown;
	m_callback = t.get<pybind11::function>("callback");
	m_hitMask = t.get<int>("hit_mask");
}

void JAttack::End() {

}


void JAttack::AttachStateMachine(StateMachine * sm) {
	PlatformerState::AttachStateMachine(sm);
	m_target = Monkey::get().Get<Entity>("player");
	m_targetStateMachine = m_target->GetComponent<StateMachine>();
	m_collision = Engine::get().GetRunner<ICollisionEngine>();
	auto cbounds = m_entity->GetComponent<ICollider>()->getControllerBounds();
	m_colliderWidth = cbounds.GetSize()[0];
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
			// shift


	} else {
		if (m_dynamics->m_velocity.y < 0) {
			m_animator->SetAnimation(m_animDown);
			m_targetVelocityX = 0.0f;
			m_dynamics->m_velocity.y = -m_speedDown;

			// check collision with player
			auto rect = std::make_shared<Rect>(m_colliderWidth, 2.0f, glm::vec3(-m_colliderWidth*0.5f, 0.0f, 0.0f));
			glm::mat4 tr = glm::translate(m_entity->GetPosition());
			auto result = m_collision->ShapeCast(rect.get(), tr, m_hitMask);
			if (result.report.collide) {


				bool handled = m_callback(Wrap1::create(m_entity)).cast<bool>();
				if (handled) {
					return;
				}
			}
		}
	}

	glm::vec3 delta = m_dynamics->step(dt, m_targetVelocityX, 0.0f);

	m_controller->Move(delta);
	if (m_controller->grounded()) {
		//std::cout << "ciao " << delta.y<< "\n";
		//std::cout << "bottom: " << m_controller->m_raycastOrigins.bottomLeft.y<< "\n";
		//std::cout << "y: " << m_entity->GetPosition().y << "\n";
		if (m_dynamics->m_velocity.y < 0) {
			//float deltaY = m_controller->m_raycastOrigins.bottomLeft.y - m_entity->GetPosition().y;
			//std::cout << "delta = " << deltaY << "\n";
//			m_entity->MoveOrigin(glm::vec2(0, deltaY/m_entity->GetScale()));
//			// now check the next state
//			if (m_targetStateMachine->GetState() == "stomped")
				//m_sm->SetState("landed");
//				m_callback(Wrap1::create(m_entity));
//			else
			m_sm->SetState("walk");
			return;
		}
	}
	UpdateAnimation();


}