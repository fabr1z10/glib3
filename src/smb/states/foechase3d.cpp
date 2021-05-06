#include "foechase3d.h"
#include <monkey/components/controller3d.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/entity.h>
#include <monkey/components/animator.h>
#include <monkey/random.h>
#include <monkey/model/boxedmodel.h>
#include <monkey/input/pytab.h>


FoeChase3D::FoeChase3D(const ITab& t) : State(t) {
	m_walkAnim = t.get<std::string>("walkanim");
	m_idleAnim = t.get<std::string>("idleanim");
	m_speed = t.get<float>("speed");
	m_acceleration = t.get<float>("acceleration");
	float cumProb = 0.0f;
//
//	t.foreach("attacks", [&] (const ITab& dict) {
//		auto state = dict.get<std::string>("state");
//		auto prob = dict.get<float>("prob");
//		auto inRange = dict.get<bool> ("in_range");
//		cumProb += prob;
//		m_attackMap.insert(std::make_pair(cumProb, m_attacks.size()));
//		m_attacks.push_back( AttackInfo {state, prob, inRange});
//	});

	//m_attacks = t.get<std::vector<std::string>>("attacks");
}

void FoeChase3D::AttachStateMachine(StateMachine * sm) {
	//PlatformerState::AttachStateMachine(sm);
	m_entity = sm->GetObject();
	m_animator = m_entity->GetComponent<IAnimator>();
	m_controller = dynamic_cast<Controller3D*>(m_entity->GetComponent<IController>());
	m_dynamics = m_entity->GetComponent<Dynamics2D>();

	m_target = Monkey::get().Get<Entity>("player");
}

float FoeChase3D::computeDirection() {

}

void FoeChase3D::Init(pybind11::dict& d) {
	PyTab dict(d);
	if (dict.has("left")) {
		m_left = dict.get<int>("left");
	}
	m_inRange = false;
	//m_c->UpdateRaycastOrigins();
	// character will go towards player
	float scale = m_entity->GetScale();
	//m_attackPos = scale * dynamic_cast<BoxedModel*>(m_animator->getModel())->getAttackDistance();
	m_attackPos = scale * m_entity->GetComponent<ICollider>()->getAttackDistance();

	//setDirection(m_left);
	computeDirection();
}



void FoeChase3D::Run(double dt) {
	if (m_controller->grounded()) {
		m_dynamics->m_velocity.y = 0.0f;
		auto targetPos = m_target->GetPosition();
		auto entityPos = m_entity->GetPosition();
		float x0 = targetPos.x - m_attackPos;
		float x1 = targetPos.x + m_attackPos;
		glm::vec3 targetPoint(entityPos.x > targetPos.x ? x1 : x0, targetPos.y, targetPos.z);
		float dist {0.0f};
		float eps = 0.1f;
		m_inRange = false;
		glm::vec3 displacement = glm::normalize(targetPoint - entityPos) * m_speed;
		displacement.y = 0.0f;
		std::cerr << glm::length(displacement) << "\n";
		m_targetVelocityX = displacement.x;
		m_targetVelocityZ = displacement.z;
		glm::vec3 delta = m_dynamics->step(dt, m_targetVelocityX, m_targetVelocityZ, m_acceleration);
		m_controller->Move(delta);
	} else {

		m_animator->SetAnimation(m_walkAnim);
		glm::vec3 delta = m_dynamics->step(dt, 0.0f, m_acceleration);
		m_controller->Move(delta);
	}
}

void FoeChase3D::End() {}