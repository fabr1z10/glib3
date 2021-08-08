#include "jump3d.h"

#include <monkey/components/inputmethod.h>
#include <monkey/components/controller3d.h>
#include <monkey/entity.h>
#include <monkey/math/geom.h>

#include <monkey/components/dynamics2d.h>
#include <monkey/components/animator.h>
#include <GLFW/glfw3.h>

Jump3D::Jump3D(float accelerationTimeAirborne, float speed, bool flipH, const std::string& animUp, const std::string& animDown) :
        m_accTimeAir(accelerationTimeAirborne), m_speed(speed), m_flipHorizontally(flipH), m_jumpAnimUp(animUp), m_jumpAnimDown(animDown)
{}


Jump3D::Jump3D(const ITab& t) : State(t) {
	m_speed = t.get<float>("speed");
	m_accTimeAir = t.get<float>("acceleration");
	m_flipHorizontally = t.get<bool>("flipH");
	m_jumpAnimUp = t.get<std::string>("animUp", "jumpup");
	m_jumpAnimDown = t.get<std::string>("animDown", "jumpdown");
}


void Jump3D::AttachStateMachine(StateMachine * sm) {
	State::AttachStateMachine(sm);
	m_entity = sm->GetObject();
	m_controller = dynamic_cast<Controller3D *>(m_entity->GetComponent<IController>());
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

void Jump3D::Run(double dt) {
    // if not touching the ground, set status to jump
    bool left = m_input->isKeyDown(GLFW_KEY_LEFT);
    bool right = m_input->isKeyDown(GLFW_KEY_RIGHT);
    bool up = m_input->isKeyDown(GLFW_KEY_UP);
    bool down = m_input->isKeyDown(GLFW_KEY_DOWN);

    m_vy0 = m_dynamics->m_velocity.y;

    if (m_controller->grounded() && m_dynamics->m_velocity.y < 0) {
        if (!m_bounce) {
            m_dynamics->m_velocity.y = 0.0f;
            m_sm->SetState("walk");
        } else {
            m_dynamics->m_velocity.y = m_bounceFactor * m_dynamics->m_velocity.y;
        }
        return;
    }

    // bump head
    if (m_controller->ceiling())	{
        m_dynamics->m_velocity.y = 0;
        //m_animator->SetAnimation(m_jumpAnimDown);
    }

    float targetVelocityX = 0.0f;
    float targetVelocityZ = 0.0f;
    if (left || right) {
        if (m_flipHorizontally) {
            m_entity->SetFlipX(left);
            targetVelocityX = m_speed;
        } else {
            targetVelocityX = (left ? -1.0f : 1.0f) * m_speed;
        }

    }
    if (up) {
        targetVelocityZ = -m_speed;
    } else if (down) {
        targetVelocityZ = m_speed;
    }
    glm::vec3 delta = m_dynamics->step(dt, targetVelocityX, targetVelocityZ, m_accTimeAir);
    m_controller->Move(delta);
    std::cerr << "y = " << m_entity->GetPosition().y << "\n";
    // UpdateAnimation();
	//m_animator->SetAnimation("jump");
    if (m_dynamics->m_velocity.y >=  0) {
        m_animator->SetAnimation(m_jumpAnimUp);
    } else {
        m_animator->SetAnimation(m_jumpAnimDown);
    }
}
