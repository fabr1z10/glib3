#include "monkey/states/playerjump3d.h"

#include <monkey/components/inputmethod.h>
#include <monkey/components/controller3d.h>
#include <monkey/entity.h>
#include <monkey/math/geom.h>

#include <monkey/components/dynamics2d.h>
#include <monkey/components/animator.h>
#include <GLFW/glfw3.h>

//Jump3D::Jump3D(float accelerationTimeAirborne, float speed, bool flipH, const std::string& animUp, const std::string& animDown) :
//        m_accTimeAir(accelerationTimeAirborne), m_speed(speed), m_flipHorizontally(flipH), m_jumpAnimUp(animUp), m_jumpAnimDown(animDown)
//{}


PlayerJump3D::PlayerJump3D(const ITab& t) : State(t) {
	m_maxSpeed = t.get<float>("max_speed");
    auto tmax = t.get<float>("time_acc");
    m_acceleration = m_maxSpeed / tmax;
    m_gravity = t.get<float>("gravity");
    m_walkState = t.get<std::string>("walk_state", "walk");
    //m_flipHorizontally = t.get<bool>("flipH");
	m_jumpAnimUp = t.get<std::string>("animUp", "jumpup");
	m_jumpAnimDown = t.get<std::string>("animDown", "jumpdown");
}


void PlayerJump3D::AttachStateMachine(StateMachine * sm) {
	State::AttachStateMachine(sm);
	m_entity = sm->GetObject();
	m_controller = dynamic_cast<Controller3D *>(m_entity->GetComponent<IController>());
	if (m_controller == nullptr) {
		GLIB_FAIL("Platformer state requires a <Controller3D> component!");
	}
    m_renderer = dynamic_cast<AnimationRenderer*>(m_entity->GetComponent<Renderer>());

	m_dynamics = m_entity->GetComponent<Dynamics3D>();
	if (m_dynamics == nullptr) {
		GLIB_FAIL("Platormer state requires a <Dynamics3D> component!");
	}
	//m_animator = m_entity->GetComponent<Animator>();
	m_input = m_entity->GetComponent<InputMethod>();
	//if (m_input == nullptr) {
	//    GLIB_FAIL("Walk state requires an <InputMethod> component!");
	//}
	// TODO set animator
	//m_animator = m_entity->GetComponent<IAnimator>();
}

void PlayerJump3D::Run(double dt) {
    float dtf = static_cast<float>(dt);

    if (m_controller->grounded() && m_dynamics->m_velocity.y < 0) {
        // landed on a platform
        m_dynamics->m_velocity.y = 0.0f;

        m_sm->SetState(m_walkState);
        return;
    }

    // bump head
    if (m_controller->ceiling()) {
        m_dynamics->m_velocity.y = 0;
    }


    bool left = m_input->isKeyDown(GLFW_KEY_LEFT);
    bool right = m_input->isKeyDown(GLFW_KEY_RIGHT);
    bool up = m_input->isKeyDown(GLFW_KEY_UP);
    bool down = m_input->isKeyDown(GLFW_KEY_DOWN);

    glm::vec3 a(0.0f);
    a.y = -m_gravity;

    if (left || right) {
        a.x = m_acceleration;
        m_entity->SetFlipX(left);
    } else {
        // apply deceleration only if velocity above theshold
        if (fabs(m_dynamics->m_velocity.x) > 0.1f) {
            a.x = -m_acceleration;
        } else {
            a.x = 0.0f;
            m_dynamics->m_velocity.x = 0.0f;
        }
    }
    if (up || down) {
        a.z = (down ? 1.0f : -1.0f) * m_acceleration;
    } else {
        // apply deceleration only if velocity above theshold
        if (fabs(m_dynamics->m_velocity.z) > 0.1f) {
            a.z = -signf(m_dynamics->m_velocity.z) * m_acceleration;
        } else {
            a.z = 0.0f;
            m_dynamics->m_velocity.z = 0.0f;
        }
    }

    m_dynamics->m_velocity += a * dtf;
    // limit horizontal vel to max speed
    if (left || right) {
        if (fabs(m_dynamics->m_velocity.x > m_maxSpeed)) {
            m_dynamics->m_velocity.x = sign(m_dynamics->m_velocity.x) * m_maxSpeed;
        }
    }

    auto delta = m_dynamics->m_velocity * dtf;
    //m_entity->MoveLocal(delta);
    std::cerr << delta.z << std::endl;
    m_controller->Move(delta);
//    if (m_renderer != nullptr) {
//        if (m_dynamics->m_velocity.y >= 0) {
//            m_renderer->setAnimation(m_jumpUpAnim);
//        } else {
//            m_renderer->setAnimation(m_jumpDownAnim);
//        }
//    }
}
