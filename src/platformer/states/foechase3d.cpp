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
	t.foreach("attacks", [&] (const ITab& dict) {
		auto state = dict.get<std::string>("state");
		auto prob = dict.get<float>("prob");
		auto inRange = dict.get<bool> ("in_range");
		cumProb += prob;
		m_attackMap.insert(std::make_pair(cumProb, m_attacks.size()));
		m_attacks.push_back( AttackInfo {state, prob, inRange});
	});
}

void FoeChase3D::AttachStateMachine(StateMachine * sm) {
	State::AttachStateMachine(sm);
	m_entity = sm->GetObject();
	m_animator = m_entity->GetComponent<IAnimator>();
	m_controller = dynamic_cast<Controller3D*>(m_entity->GetComponent<IController>());
	m_dynamics = m_entity->GetComponent<Dynamics2D>();

	m_target = Monkey::get().Get<Entity>("player");
}

float FoeChase3D::computeDirection() {

}

void FoeChase3D::Init(const ITab& d) {
	if (d.has("left")) {
		m_left = d.get<int>("left");
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



bool FoeChase3D::randomAttack(glm::vec3 displacement) {
    if (fabs(displacement.z) < 0.1f && fabs(displacement.x) <= m_attackPos + 0.1f) {
        float u = Random::get().GetUniformReal(0.0f, 1.0f);
        auto iter = m_attackMap.lower_bound(u);
        if (iter != m_attackMap.end()) {
            const auto &attack = m_attacks[iter->second];
            m_sm->SetState(attack.nextState);
            return true;
        }
    }
    return false;
}

void FoeChase3D::Run(double dt) {
	if (m_controller->grounded()) {
		m_dynamics->m_velocity.y = 0.0f;
		auto targetPos = m_target->GetPosition();
		auto entityPos = m_entity->GetPosition();
		float x0 = targetPos.x - m_attackPos;
		float x1 = targetPos.x + m_attackPos;
		bool rightOfPlayer = entityPos.x > targetPos.x;
		glm::vec3 targetPoint(rightOfPlayer ? x1 : x0, targetPos.y, targetPos.z);
        m_entity-> SetFlipX(rightOfPlayer);

        // if we are within range, randomly attack




        float dist {0.0f};
		float eps = 0.1f;
		m_inRange = false;
		auto displacement = (targetPoint - entityPos);
		displacement.y = 0;
       if (randomAttack(displacement)) {
            return;
        }


		if (glm::length(displacement) > 0.01f) {
            m_animator->SetAnimation(m_walkAnim);

            auto velocity = glm::normalize(displacement) * m_speed;

            std::cerr << glm::length(displacement) << "\n";
			//fabs(entityPos.x - targetPos.x) > m_attackPos
			m_targetVelocityX = fabs(entityPos.x - targetPos.x) > m_attackPos ? fabs(velocity.x) : -fabs(velocity.x);
            m_targetVelocityZ = velocity.z;
            glm::vec3 delta = m_dynamics->step(dt, m_targetVelocityX, m_targetVelocityZ, m_acceleration);
            if (fabs(delta.x) > fabs(displacement.x)) {
                delta.x = sign(delta.x) * fabs(displacement.x);
            }
            if (fabs(delta.z) > fabs(displacement.z)) {
                delta.z = sign(delta.z) * fabs(displacement.z);
            }
            m_controller->Move(delta);
        } else {
		    m_animator->SetAnimation(m_idleAnim);
		}
	} else {

		m_animator->SetAnimation(m_walkAnim);
		glm::vec3 delta = m_dynamics->step(dt, 0.0f, m_acceleration);
		m_controller->Move(delta);
	}
}

void FoeChase3D::End() {}