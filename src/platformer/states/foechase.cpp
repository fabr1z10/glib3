#include "foechase.h"
#include <monkey/components/controller2d.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/entity.h>
#include <monkey/components/animator.h>
#include <monkey/random.h>
#include <monkey/model/boxedmodel.h>
#include <monkey/input/pytab.h>

FoeChase::FoeChase(const std::string &walkAnim, const std::string &idleAnim, float speed, float acceleration,
    bool fliph, bool flipIfPlatformEnds, int left) : PlatformerState(),
m_walkAnim(walkAnim), m_idleAnim(idleAnim), m_speed(speed), m_acceleration(acceleration)
{

}

FoeChase::FoeChase(const ITab& t) : PlatformerState(t) {
    m_walkAnim = t.get<std::string>("walkanim");
    m_idleAnim = t.get<std::string>("idleanim");
    m_speed = t.get<float>("speed");
    m_acceleration = t.get<float>("acceleration");
    //m_fliph = t.get<bool>("flipH");
    // m_flipIfPlatformEnds = t.get<bool>("flipWhenPlatformEnds");
    //m_left = t.get<int>("left");
    float cumProb = 0.0f;

    t.foreach("attacks", [&] (const ITab& dict) {
    	auto state = dict.get<std::string>("state");
    	auto prob = dict.get<float>("prob");
    	auto inRange = dict.get<bool> ("in_range");
    	cumProb += prob;
    	m_attackMap.insert(std::make_pair(cumProb, m_attacks.size()));
		m_attacks.push_back( AttackInfo {state, prob, inRange});
    });

    //m_attacks = t.get<std::vector<std::string>>("attacks");
}

void FoeChase::AttachStateMachine(StateMachine * sm) {
    PlatformerState::AttachStateMachine(sm);
    m_c = dynamic_cast<Controller2D*>(m_controller);

    // here I will get the skeletal model or sprite model
    auto animator = sm->GetObject()->GetComponent<IAnimator>();

	float scale = m_entity->GetScale();
    m_attackPos = scale * m_entity->GetComponent<ICollider>()->getAttackDistance();
    //m_attackPos = scale * dynamic_cast<BoxedModel*>(animator->getModel())->getAttackDistance();

//    auto shapes = animator->getModel()->getAttackShapes();
//    float am = -std::numeric_limits<float>::infinity();
//    float aM = std::numeric_limits<float>::infinity();
//    for (const auto& shape : shapes) {
//        auto sb = shape->getBounds();
//        am = std::max(am, scale*sb.min.x);
//        aM = std::min(aM, scale*sb.max.x);
//    }
//    m_attackPos = aM;

    m_target = Monkey::get().Get<Entity>("player");
}

float FoeChase::computeDirection() {

    float x = m_target->GetPosition().x;
    float x0 = x - m_attackPos;
    float x1 = x + m_attackPos;
    float ex = m_entity->GetPosition().x;
	float dist {0.0f};
	float eps = 0.1f;
	m_inRange = false;
	if (ex > x) {
		// enemy is right of player
		auto target = x1;
		dist = fabs(target - ex);
		// check if we have reached the target
		if (dist < eps) {
			m_inRange = true;
		} else {
			m_entity-> SetFlipX(true);
			if (ex > x1) {
				m_targetVelocityX = m_speed;
			} else {
				m_targetVelocityX = -m_speed;
			}
		}
	} else {
		// enemy is left of player
		auto target = x0;
		dist = fabs(target - ex);
		// check if we have reached the target
		if (dist < eps) {
			m_inRange = true;
		} else {
			m_entity-> SetFlipX(false);
			if (ex < x0) {
				m_targetVelocityX = m_speed;
			} else {
				m_targetVelocityX = -m_speed;
			}
		}
	}

    //std::cout << abs(ex-x) << ", " << m_attackPos << abs(abs(ex-x)-m_attackPos) << "\n";
    if (m_inRange) {
        m_animator->SetAnimation(m_idleAnim);
        m_targetVelocityX = 0.0f;
    } else {
        m_animator->SetAnimation(m_walkAnim);
    }
	return dist;

}

void FoeChase::Init(pybind11::dict& d) {
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


bool FoeChase::randomAttack(float displacement) {
	if (fabs(displacement) <= m_attackPos + 0.1f) {
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

void FoeChase::Run(double dt) {

    if (m_controller->grounded()) {
        m_dynamics->m_velocity.y = 0.0f;
        auto targetPos = m_target->GetPosition();
        auto entityPos = m_entity->GetPosition();
        float x0 = targetPos.x - m_attackPos;
        float x1 = targetPos.x + m_attackPos;
        bool rightOfPlayer = entityPos.x > targetPos.x;
        float targetPoint = rightOfPlayer ? x1 : x0;
        m_entity-> SetFlipX(rightOfPlayer);
        float dist {0.0f};
        float eps = 0.1f;
        m_inRange = false;
        auto displacement = (targetPoint - entityPos.x);
        if (randomAttack(displacement)) {
            return;
        }

        if (fabs(displacement) > 0.01f) {
            m_animator->SetAnimation(m_walkAnim);
            std::cerr << glm::length(displacement) << "\n";
            m_targetVelocityX = fabs(entityPos.x - targetPos.x) > m_attackPos ? m_speed : -m_speed;
            glm::vec3 delta = m_dynamics->step(dt, m_targetVelocityX, m_acceleration);
            if (fabs(delta.x) > fabs(displacement)) {
                delta.x = sign(delta.x) * fabs(displacement);
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

void FoeChase::End() {}