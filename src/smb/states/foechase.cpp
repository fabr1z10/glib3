#include "foechase.h"
#include <monkey/components/controller2d.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/entity.h>
#include <monkey/components/animator.h>
#include <monkey/random.h>
#include <GLFW/glfw3.h>

FoeChase::FoeChase(const std::string &walkAnim, const std::string &idleAnim, float speed, float acceleration,
    bool fliph, bool flipIfPlatformEnds, int left) : PlatformerState(),
m_walkAnim(walkAnim), m_idleAnim(idleAnim), m_speed(speed), m_acceleration(acceleration)
{

}

FoeChase::FoeChase(const ITable & t) : PlatformerState(t) {
    m_walkAnim = t.get<std::string>("walkanim");
    m_idleAnim = t.get<std::string>("idleanim");
    m_speed = t.get<float>("speed");
    m_acceleration = t.get<float>("acceleration");
    //m_fliph = t.get<bool>("flipH");
    // m_flipIfPlatformEnds = t.get<bool>("flipWhenPlatformEnds");
    //m_left = t.get<int>("left");
    float cumProb = 0.0f;
    t.foreach<PyDict>("attacks", [&] (const PyDict& dict) {
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
    auto shapes = animator->getModel()->getAttackShapes();
    float am = -std::numeric_limits<float>::infinity();
    float aM = std::numeric_limits<float>::infinity();
    float scale = m_entity->GetScale();
    for (const auto& shape : shapes) {
        auto sb = shape->getBounds();
        am = std::max(am, scale*sb.min.x);
        aM = std::min(aM, scale*sb.max.x);
    }
    m_attackPos = 0.5f* (am+aM);

    m_target = Monkey::get().Get<Entity>("player");
}

void FoeChase::computeDirection() {

    float x = m_target->GetPosition().x;
    float x0 = x - m_attackPos;
    float x1 = x + m_attackPos;
    float ex = m_entity->GetPosition().x;
    if (ex > x1) {
        // go left, face left
        m_entity-> SetFlipX(true);
        m_targetVelocityX = m_speed;
    } else if (ex < x0) {
        // go right, face right
        m_entity->SetFlipX(false);
        m_targetVelocityX = m_speed;
    } else if (ex >= x0 && ex < x) {
        // go left, face right
        m_entity->SetFlipX(false);
        m_targetVelocityX = -m_speed;
    } else if (ex >=x && ex < x1) {
        // go right, face left
        m_entity->SetFlipX(true);
        m_targetVelocityX = -m_speed;
    }
    //m_inRange =abs(abs(ex-x)-m_attackPos) < 0.2f;
	m_inRange =abs(ex-x) < m_attackPos;
    //std::cout << abs(ex-x) << ", " << m_attackPos << abs(abs(ex-x)-m_attackPos) << "\n";
    if (m_inRange) {
        m_animator->SetAnimation(m_idleAnim);
        m_targetVelocityX = 0.0f;
    } else {
        m_animator->SetAnimation(m_walkAnim);
    }


}

void FoeChase::Init(pybind11::dict& d) {
    PyDict dict(d);
    if (dict.hasKey("left")) {
        m_left = dict.get<int>("left");
    }
    m_inRange = false;
    m_c->UpdateRaycastOrigins();
    // character will go towards player


    //setDirection(m_left);
    computeDirection();
}



void FoeChase::Run(double dt) {



    if (m_controller->grounded()) {

        m_dynamics->m_velocity.y = 0.0f;
        computeDirection();
        // if I'm at the right position, go to idle
        // randomly attack if within range
		float u = Random::get().GetUniformReal(0.0f, 1.0f);
		auto iter = m_attackMap.lower_bound(u);
		if (iter != m_attackMap.end()) {
			const auto& attack = m_attacks[iter->second];
			if (!attack.inRange || m_inRange) {
				m_sm->SetState(attack.nextState);
			}
		}


//		if (m_inRange) {
//            float u = Random::get().GetUniformReal(0.0f, 1.0f);
//            if (u < m_probAttack) {
//                int chosenAttack = Random::get().GetUniform(0, m_attacks.size()-1);
//                m_sm->SetState(m_attacks[chosenAttack]);
//            }
//
//        }
        //if (!m_c->IsFalling( m_targetVelocityX > 0 ? 1 : -1)) {
        if (!m_inRange) {
            glm::vec3 delta = m_dynamics->step(dt, m_targetVelocityX, m_acceleration);
            //if (m_speed < 30.0f) std::cout << delta.x << "\n";
            // before moving, check if I'm falling off the platform

            m_controller->Move(delta);
        }
    } else {

        m_animator->SetAnimation(m_walkAnim);
        glm::vec3 delta = m_dynamics->step(dt, 0.0f, m_acceleration);
        m_controller->Move(delta);
    }


//	if (m_jumpAttack) {
//		float u = Random::get().GetUniformReal(0.0f, 1.0f);
//		if (u < 0.005f) {
//			m_animator->SetAnimation("jumpup");
//			auto targetPos = m_target->GetPosition();
//			auto mePos = m_entity->GetPosition();
//			float dxToCover = targetPos.x - mePos.x;
//			float js = 1000.0f;
//			float tja = (js/fabs(m_dynamics->m_gravity));
//			m_targetVelocityX = dxToCover / tja;
//			if (m_entity->GetFlipX()) {
//				m_targetVelocityX *= -1.0f;
//			}
//			m_targetVelocityY = dzToCover / tja;
//			m_dynamics->m_velocity.y = js;
//			m_jumping = true;
//		}
//	}

//    if ((m_left && m_c->m_details.left) || (!m_left && m_c->m_details.right)) {
//        // I bumped into a wall
//        m_left = (m_left == 0 ? 1 : 0);
//        setDirection(m_left);
//    }
//    if (m_flipIfPlatformEnds) {
//        // check if I reached the end of the platform
//        if (m_c->m_details.below && m_c->IsFalling((m_left==1) ? -1 : 1)) {
//            m_left = (m_left == 0 ? 1 : 0);
//            setDirection(m_left);
//        }
//    }


    UpdateAnimation();
}

void FoeChase::End() {}