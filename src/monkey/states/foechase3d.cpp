#include <monkey/states/foechase3d.h>
#include <monkey/components/controller3d.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/entity.h>
#include <monkey/engine.h>
#include <monkey/components/icollider.h>
#include <monkey/random.h>

FoeChase3D::FoeChase3D(const ITab& t) : Base3D(t) {
    m_idleAnim = t.get<std::string>("idle_anim", "idle");
    m_walkAnim = t.get<std::string>("walk_anim", "walk");//	m_speed = t.get<float>("speed");
//	m_acceleration = t.get<float>("acceleration");

	if (t.has("attacks")) {
        float cumOdds = 0.0f;
        std::vector<float> odds;
        std::vector<AttackDetails> details;
        int attackId = 0;
        t.foreach("attacks", [&] (const ITab& dict) {
    //		auto state = dict.get<std::string>("state");
            auto odd = dict.get<float>("prob");
			cumOdds += odd;
            odds.push_back(cumOdds);
            auto inRange = dict.get<bool> ("in_range", true);
            details.push_back({attackId++, glm::vec2(0.0f), inRange});
    //		m_attackMap.insert(std::make_pair(cumProb, m_attacks.size()));
    //		m_attacks.push_back( AttackInfo {state, prob, inRange});
        });
        cumOdds = 1.0f / cumOdds;
        //std::transform(odds.begin(), odds.end(), odds.begin(), [&cumOdds] (auto& c) {return c * cumOdds;});
        for (size_t j = 0; j < odds.size() - 1; ++j) {
            m_attackMap.insert(std::make_pair(odds[j] * cumOdds, details[j]));
        }

    }
}
//
void FoeChase3D::AttachStateMachine(StateMachine * sm) {
	Base3D::AttachStateMachine(sm);
	m_target = Monkey::get().Get<Entity>("player");
    m_collider = m_entity->GetComponent<ICollider>();
	// set the attack ranges

	m_unscaledThickness = Engine::get().getVariable<float>("data.globals.thickness");
	m_unscaledAttackRange = m_collider->getAttackDistance();
    m_unscaledAttackDistance = 0.5f * (m_unscaledAttackRange[0] + m_unscaledAttackRange[1]);
	//m_thickness = scale.z * Engine::get().getVariable<float>("data.globals.thickness");
    //m_halfThickness = 0.5f * m_thickness;
    //m_attackRange = scale.x * m_collider->getAttackDistance();
    //m_attackDistance = 0.5f * (m_attackRange[0] + m_attackRange[1]);

	int attackId = 0;
	for (auto& a : m_attackMap) {
	    if (a.second.inRange) {
	        a.second.range = m_collider->getAttackRange("attack_" + std::to_string(attackId));
	    }
	    attackId++;
	}
}
//
//float FoeChase3D::computeDirection() {
//
//}
//
void FoeChase3D::Init(const ITab& d) {


    // loop through

//	if (d.has("left")) {
//		m_left = d.get<int>("left");
//	}
//	m_inRange = false;
//	//m_c->UpdateRaycastOrigins();
//	// character will go towards player
//	//m_attackPos = scale * dynamic_cast<BoxedModel*>(m_animator->getModel())->getAttackDistance();
//	m_attackPos = scale * m_entity->GetComponent<ICollider>()->getAttackDistance();
//
//	//setDirection(m_left);
//	computeDirection();
}
//
//
//
// returns whether attack is performed
bool FoeChase3D::randomAttack(float dx, float scaleX) {

    float u = Random::get().GetUniformReal(0.0f, 1.0f);
    auto iter = m_attackMap.lower_bound(u);
    while (iter != m_attackMap.end()) {
        if (!iter->second.inRange || (dx > scaleX * iter->second.range[0] && dx < scaleX * iter->second.range[1])) {
            std::string nextState = "attack_" + std::to_string(iter->second.attackId);
            m_sm->SetState(nextState);
            return true;
        }
        iter++;
    }
    return false;
}

void FoeChase3D::Run(double dt) {
    auto dtf = static_cast<float>(dt);
    auto scale = m_entity->getScaleVec();
    m_thickness = scale.z * m_unscaledThickness;
    m_attackRange = scale.x * m_unscaledAttackRange;
    m_attackDistance = 0.5f * (m_attackRange[0] + m_attackRange[1]);
//	if (m_controller->grounded() && m_dynamics->m_velocity.y <=0) {
//        m_dynamics->m_velocity.y = 0.0f;
//    }
//
	auto targetPos = m_target->GetPosition();
	auto entityPos = m_entity->GetPosition();

	float x0 = targetPos.x - m_attackDistance;
	float x1 = targetPos.x + m_attackDistance;
	bool rightOfPlayer = entityPos.x > targetPos.x;
	glm::vec3 targetPoint(rightOfPlayer ? x1 : x0, targetPos.y, targetPos.z);


	m_entity-> SetFlipX(rightOfPlayer);
	auto d = targetPos - entityPos;
	float dx = d.x * (m_entity->GetFlipX() ? -1.0f : 1.0f);
    m_inRange = true;//(fabs(d.z) < m_halfThickness) &&
            //(dx > m_attackRange[0] && dx < m_attackRange[1]);
    if (m_inRange) {
        // attack with probability p_attack
        //std::cout << "qui;";
        if (randomAttack(dx, scale.x)) {
            //std::cout << dx << ", " << d.z << ", " << m_halfThickness << " " << m_attackRange[0] << " " << m_attackRange[1] << "\n";
            return;
        }
    }

    // find current displacement
    auto displacement = targetPoint - entityPos;
    displacement.y = 0.0f;

    //std::cout << dx << ", " << d.z << ", " << m_halfThickness << " " << m_attackRange[0] << " " << m_attackRange[1] << "\n";

    m_dynamics->m_velocity.y = -m_gravity * dtf;
    auto dl = glm::length(displacement);
	if (dl > 0.1f) {
		m_renderer->setAnimation(m_walkAnim);
		float maxSpeed = (dl / dtf) > m_maxSpeed ? m_maxSpeed : (dl /dtf);
		auto velocity = glm::normalize(displacement) * maxSpeed;
		m_dynamics->m_velocity.x = fabs(entityPos.x - targetPos.x) > m_attackDistance ? fabs(velocity.x) : -fabs(velocity.x);
		m_dynamics->m_velocity.z = velocity.z;
		auto delta = m_dynamics->m_velocity * dtf;
		m_controller->Move(delta);
	} else {
		m_dynamics->m_velocity = glm::vec3(0.0f);
		auto delta = m_dynamics->m_velocity * dtf;
		m_controller->Move(delta);
		if (m_controller->grounded()) {
			m_renderer->setAnimation(m_idleAnim);
		} else {
			m_renderer->setAnimation(m_walkAnim);
		}
	}


    return;

    //m_inRange = fabs(fabs(targetPos.x - entityPos.x) - m_attackDistance) < 0.1f && fabs(targetPos.z - entityPos.z) < 0.1f;
//	glm::vec3 displacement(0.0f);
//	if (!m_inRange) {
//        // if we are within range, randomly attack
//        float dist{0.0f};
//        float eps = 0.1f;
//        displacement = (targetPoint - entityPos);
//        displacement.y = 0;
//    }
    //if (m_controller->grounded() && randomAttack(displacement)) {
       // return;
   // }


    m_dynamics->m_velocity.y = -m_gravity * dtf;

	if (glm::length(displacement) > 0.01f) {
	    m_renderer->setAnimation(m_walkAnim);
	    auto velocity = glm::normalize(displacement) * m_maxSpeed;
	    m_dynamics->m_velocity.x = fabs(entityPos.x - targetPos.x) > m_attackDistance ? fabs(velocity.x) : -fabs(velocity.x);
	    m_dynamics->m_velocity.z = velocity.z;
//
//	    m_targetVelocityX = fabs(entityPos.x - targetPos.x) > m_attackPos ? fabs(velocity.x) : -fabs(velocity.x);
//	    m_targetVelocityZ = velocity.z;
//	    glm::vec3 delta = m_dynamics->step(dt, m_targetVelocityX, m_targetVelocityZ, m_acceleration);
//	    if (fabs(delta.x) > fabs(displacement.x)) {
//	        delta.x = sign(delta.x) * fabs(displacement.x);
//	    }
//	    if (fabs(delta.z) > fabs(displacement.z)) {
//	        delta.z = sign(delta.z) * fabs(displacement.z);
//	    }
        auto delta = m_dynamics->m_velocity * dtf;
        m_controller->Move(delta);
//	    if (m_controller->grounded() && (m_controller->m_details.front || m_controller->m_details.back || m_controller->m_details.left || m_controller->m_details.right)) {
//	        std::cerr << "BLOCKED!\n";
//	        m_dynamics->m_velocity.y = 10.0f;
//	    }
	} else {
	    m_dynamics->m_velocity = glm::vec3(0.0f);
        auto delta = m_dynamics->m_velocity * dtf;
        m_controller->Move(delta);
        if (m_controller->grounded()) {
            m_renderer->setAnimation(m_idleAnim);
        } else {
            m_renderer->setAnimation(m_walkAnim);
        }
	}
//        glm::vec3 delta = m_dynamics->step(dt, m_targetVelocityX, m_targetVelocityZ, m_acceleration);
//        delta.x = 0.0f;
//        delta.z = 0.0f;
//        m_controller->Move(delta);
//
//	    }
}
////	} else {
////
////		m_animator->SetAnimation(m_walkAnim);
////		glm::vec3 delta = m_dynamics->step(dt, 0.0f, m_acceleration);
////		m_controller->Move(delta);
////	}
//}
//
void FoeChase3D::End() {}