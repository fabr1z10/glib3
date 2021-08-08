#include "walkside3d.h"

#include <monkey/math/geom.h>

#include <monkey/entity.h>
#include <monkey/components/controller3d.h>
#include <monkey/components/inputmethod.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/components/animator.h>
#include <monkey/components/statemachine.h>
#include <GLFW/glfw3.h>

WalkSide3D::WalkSide3D(float speed, float acceleration, bool fliph, float jumpSpeed) :
        m_speed(speed), m_acceleration(acceleration), m_flipHorizontally(fliph), m_velocitySmoothing(0.0f), m_jumpSpeed(jumpSpeed) {}

WalkSide3D::WalkSide3D(const ITab& t) : State(t), m_animator(nullptr)  {
    auto factory = Engine::get().GetSceneFactory();

    m_speed = t.get<float>("speed");
	m_acceleration = t.get<float>("acceleration");
	m_flipHorizontally = t.get<bool>("flipH");
	m_jumpSpeed = t.get<float>("jumpSpeed");
	auto pi = t["animator"];
    m_walkAnimator = factory->make2<WalkAnim>(*pi);

    //m_idleAnim = t.get<std::string>("idle_anim", "idle");
	//m_walkAnim = t.get<std::string>("walk_anim", "walk");
}

void WalkSide3D::Init(const ITab&) {

}

void WalkSide3D::End() {

}

void WalkSide3D::Run (double dt) {

    if (!m_controller->grounded()) {
        m_sm->SetState("jump");
        return;
    } else {
        m_dynamics->m_velocity.y = 0.0f;
    }

    if (m_controller->m_details.right || m_controller->m_details.left) {
    	m_dynamics->m_velocity.x = 0.0f;

    }

    bool left = m_input->isKeyDown(GLFW_KEY_LEFT);
    bool right = m_input->isKeyDown(GLFW_KEY_RIGHT);
    bool up = m_input->isKeyDown(GLFW_KEY_UP);
    bool down = m_input->isKeyDown(GLFW_KEY_DOWN);
    bool kj = m_input->isKeyDown(GLFW_KEY_A);

    if (kj) {
        m_dynamics->m_velocity.y = m_jumpSpeed;
        m_sm->SetState("jump");
        return;
    }


    float targetVelocityX = 0.0f;
    float targetVelocityZ = 0.0f;
    if (left || right) {
        if (m_flipHorizontally) {
            m_entity->SetFlipX(left);
            targetVelocityX = m_speed;
        } else {
           // targetVelocityX = (left ? -1.0f : 1.0f) * m_speed;
        }
    }
    if (up || down) {
        targetVelocityZ = (up ? -1.0f : 1.0f) * m_speed;
    }
    glm::vec3 delta =m_dynamics->step(dt, targetVelocityX, targetVelocityZ, m_acceleration);
    //if (left) {
    //	std::cerr << delta.z << " cas!\n";
    //}
    m_controller->Move(delta);
    //std::cerr << "new z = " << m_entity->GetPosition().z << "\n";

    m_walkAnimator->animate(m_animator, m_dynamics->m_velocity);
//	if (m_animator != nullptr) {
//		if (fabs(m_dynamics->m_velocity.x) > 1.0f || fabs(m_dynamics->m_velocity.z) > 1.0f) {
//			m_animator->SetAnimation(m_walkAnim);
//		} else {
//			m_animator->SetAnimation(m_idleAnim);
//		}
//	}
    //UpdateAnimation();
}




void WalkSide3D::AttachStateMachine(StateMachine * sm) {
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
	//m_animator = m_entity->GetComponent<Animator>();
	m_input = m_entity->GetComponent<InputMethod>();
	//if (m_input == nullptr) {
	//    GLIB_FAIL("Walk state requires an <InputMethod> component!");
	//}
	// TODO set animator
	//m_animator = m_entity->GetComponent<IAnimator>();


}